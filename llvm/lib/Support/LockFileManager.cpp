//===--- LockFileManager.cpp - File-level Locking Utility------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Support/LockFileManager.h"
#include "llvm/ADT/None.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Errc.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/raw_ostream.h"
#include <cerrno>
#include <chrono>
#include <ctime>
#include <memory>
#include <random>
#include <sys/stat.h>
#include <sys/types.h>
#include <system_error>
#include <thread>
#include <tuple>

#ifdef _WIN32
#include <windows.h>
#endif
#if LLVM_ON_UNIX
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#endif

#if defined(__APPLE__) &&                                                      \
    defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) &&                  \
    (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1050)
#define USE_OSX_GETHOSTUUID 1
#else
#define USE_OSX_GETHOSTUUID 0
#endif

#if USE_OSX_GETHOSTUUID
#include <uuid/uuid.h>
#endif

namespace llvm {
class LockFileReader {
  SmallString<256> UniqueLockFileName;
  int UniquePipeFD;

  StringRef HostID; // Referes UniqueLockFileName
  int PID;

  LockFileReader() = delete;

public:
  LockFileReader(StringRef LockFileName);
  ~LockFileReader();

  bool processStillExecuting();
  void Wait(unsigned long WaitDurationMS);

  static std::unique_ptr<LockFileReader> subscribe(StringRef LockFileName) {
    if (auto p = std::make_unique<LockFileReader>(LockFileName)) {
      if (p->UniquePipeFD > 0)
        return p;
    }
    return nullptr;
  }
};

class LockFileWriter {
  StringRef LockFileName;
  bool Acquired;

  SmallString<256> UniqueLockFileName;
  int UniquePipeFD;

  LockFileWriter() = delete;

public:
  LockFileWriter(StringRef LockFileName_, std::error_code &ErrorCode,
                 std::string &ErrorDiagMsg);
  ~LockFileWriter();

  static std::unique_ptr<LockFileWriter> create(StringRef LockFileName,
                                                std::error_code &ErrorCode,
                                                std::string &ErrorDiagMsg) {
    auto tWriter =
        std::make_unique<LockFileWriter>(LockFileName, ErrorCode, ErrorDiagMsg);
    if (ErrorCode)
      return nullptr;
    return tWriter;
  }

  std::error_code acquire();
};
} // namespace llvm

using namespace llvm;

/// Attempt to read the lock file with the given name, if it exists.
///
/// \param LockFileName The name of the lock file to read.
///
/// \returns The process ID of the process that owns this lock file
LockFileReader::LockFileReader(StringRef LockFileName) {
  char linkpath[PATH_MAX];
  ssize_t linkpathlen;

  UniquePipeFD = 0;

  // Read the owning host and PID out of the lock file. If it appears that the
  // owning process is dead, the lock file is invalid.
  std::string tLockFileName(LockFileName.begin(), LockFileName.end());
  auto pLockFileName = tLockFileName.c_str();
  for (int i = 0; i < 16; ++i) {
    linkpathlen = ::readlink(pLockFileName, linkpath, sizeof(linkpath));
    if (linkpathlen <= 0) {
      // error
      if (!UniqueLockFileName.empty())
        fprintf(stderr, "%d\t[FAILED](%zd)\t%s\n", ::getpid(), linkpathlen,
                pLockFileName);
      sys::fs::remove(LockFileName);
      return;
    }

    linkpath[linkpathlen] = 0;
    if (UniqueLockFileName != linkpath) {
      if (!UniqueLockFileName.empty())
        fprintf(stderr, "%d\t[---]\t%s\n\t[+++]\t%s\n", ::getpid(),
                UniqueLockFileName.c_str(), linkpath);
      UniqueLockFileName = linkpath;
    }

    UniquePipeFD = ::open(UniqueLockFileName.c_str(), O_RDONLY | O_NONBLOCK);
    if (UniquePipeFD <= 0)
      continue;

    fprintf(stderr, "%d\t[OPENRD]%d\t%s\n", ::getpid(), UniquePipeFD,
            UniqueLockFileName.c_str());

    // Decode HostID and PID in the link, ...#HostID#PID#...
    SmallVector<StringRef, 4> toks;
    SplitString(UniqueLockFileName, toks, "#");
    if (toks.size() >= 3 && !toks[2].getAsInteger(10, PID)) {
      HostID = toks[1];
      if (processStillExecuting()) {
        return;
      }
    }

    // Error -- unable to decode the link
    break;
  }

  // Delete the lock file. It's invalid anyway.
  sys::fs::remove(LockFileName);

  // close(FD) shall be done in the destructor.
}

LockFileReader::~LockFileReader() {
  if (UniquePipeFD > 0) {
    fprintf(stderr, "%d\t[~CLOSE]%d\t%s\n", ::getpid(), UniquePipeFD,
            UniqueLockFileName.c_str());
    ::close(UniquePipeFD);
  }
}

static std::error_code getHostID(SmallVectorImpl<char> &HostID) {
  HostID.clear();

#if USE_OSX_GETHOSTUUID
  // On OS X, use the more stable hardware UUID instead of hostname.
  struct timespec wait = {1, 0}; // 1 second.
  uuid_t uuid;
  if (gethostuuid(uuid, &wait) != 0)
    return std::error_code(errno, std::system_category());

  uuid_string_t UUIDStr;
  uuid_unparse(uuid, UUIDStr);
  StringRef UUIDRef(UUIDStr);
  HostID.append(UUIDRef.begin(), UUIDRef.end());

#elif LLVM_ON_UNIX
  char HostName[256];
  HostName[255] = 0;
  HostName[0] = 0;
  gethostname(HostName, 255);
  StringRef HostNameRef(HostName);
  HostID.append(HostNameRef.begin(), HostNameRef.end());

#else
  StringRef Dummy("localhost");
  HostID.append(Dummy.begin(), Dummy.end());
#endif

  return std::error_code();
}

static std::error_code getLockFileID(std::string &ID) {
  SmallString<256> HostID;
  if (auto EC = getHostID(HostID)) {
    return EC;
  }

  raw_string_ostream OSS(ID);
  OSS << ".#" << HostID << '#' << sys::Process::getProcessId() << '#';

  return std::error_code();
}

bool LockFileReader::processStillExecuting() {
#if LLVM_ON_UNIX && !defined(__ANDROID__)
  SmallString<256> StoredHostID;
  if (getHostID(StoredHostID))
    return true; // Conservatively assume it's executing on error.

  // Check whether the process is dead. If so, we're done.
  if (StoredHostID == HostID && getsid(PID) == -1 && errno == ESRCH)
    return false;
#endif

  return true;
}

void LockFileReader::Wait(unsigned long WaitDurationMS) {
  if (UniquePipeFD > 0) {
    struct pollfd fds[1];
    fds[0].fd = UniquePipeFD;
    fds[0].events = POLLIN;
    int r = ::poll(fds, 1, 300 * 1000);
    if (r == 1 && (fds[0].revents & POLLHUP)) {
      ::close(UniquePipeFD);
      fprintf(stderr, "%d\t[+ ACCLOSE]%d\t%s\n", ::getpid(), UniquePipeFD,
              UniqueLockFileName.c_str());
      UniquePipeFD = -1;
    }
  } else {
    fprintf(stderr, "%d [WAIT]\t\t\t%s\n", ::getpid(),
            UniqueLockFileName.c_str());
    std::this_thread::sleep_for(std::chrono::milliseconds(WaitDurationMS));
  }
}

static std::error_code createUniquePipe(const Twine &Model,
                                        SmallVectorImpl<char> &ResultPath) {
  std::error_code EC;
  SmallString<256> tResultPath;
  for (int i = 64; i >= 0; --i) {
    if (!(EC = sys::fs::getPotentiallyUniqueFileName(Model, tResultPath))) {
      if (::mkfifo(tResultPath.c_str(), 0666) < 0) {
        EC = std::error_code(errno, std::generic_category());
        continue;
      }
      ResultPath = tResultPath;
      return std::error_code();
    }
  }

  return EC;
}

LockFileManager::LockFileManager(StringRef FileName) {
  this->FileName = FileName;
  if (std::error_code EC = sys::fs::make_absolute(this->FileName)) {
    std::string S("failed to obtain absolute path for ");
    S.append(std::string(this->FileName.str()));
    setError(EC, S);
    return;
  }
  LockFileName = this->FileName;
  LockFileName += ".lock";

  // If the lock file already exists, don't bother to try to create our own
  // lock file; it won't work anyway. Just figure out who owns this lock file.
  if ((Reader = LockFileReader::subscribe(LockFileName)))
    return;

  tryAcquire();
}

LockFileWriter::LockFileWriter(StringRef LockFileName_,
                               std::error_code &ErrorCode,
                               std::string &ErrorDiagMsg)
    : LockFileName(LockFileName_) {
  auto setError = [&](const std::error_code &EC, StringRef ErrorMsg = "") {
    ErrorCode = EC;
    ErrorDiagMsg = ErrorMsg.str();
  };

  std::string LockFileID;
  if (auto EC = getLockFileID(LockFileID)) {
     setError(EC, "failed to get host id");
    return;
  }

  // Create a pipe that is unique to this instance.
  if (std::error_code EC = createUniquePipe(
          Twine(LockFileName) + LockFileID + "-%%%%%%%%", UniqueLockFileName)) {
#if 1
    std::string S("failed to create unique pipe ");
    S.append(std::string(LockFileName.str()));
    setError(EC, S);
#endif
    UniqueLockFileName.clear();
    return;
  }

  // Clean up the unique file on signal, which also releases the lock if it is
  // held since the .lock symlink will point to a nonexistent file.
  sys::RemoveFileOnSignal(UniqueLockFileName, nullptr);

  {
    int rfd = ::open(UniqueLockFileName.c_str(), O_RDONLY | O_NONBLOCK);
    if (rfd > 0) {
      UniquePipeFD = ::open(UniqueLockFileName.c_str(), O_WRONLY | O_NONBLOCK);
#if 1
      if (UniquePipeFD <= 0) {
        auto EC = std::error_code(errno, std::generic_category());
        setError(EC, "unabled to open pipe for writing");
      }
      ::close(rfd);
#else
      if (UniquePipeFD > 0) {
      } else {
        ::close(rfd);
      }
#endif
    } else {
      auto EC = std::error_code(errno, std::generic_category());
      setError(EC, "unabled to open pipe for reading");
    }
    fprintf(stderr, "%d\t[OPENWR]%d\t%s\n", ::getpid(), UniquePipeFD,
            UniqueLockFileName.c_str());
  }
}

// FIXME: Let it inline.
void LockFileManager::tryAcquire() {
  auto tWriter = LockFileWriter::create(LockFileName, ErrorCode, ErrorDiagMsg);
  if (!tWriter)
    return;

  while (true) {
    // Create a link from the lock file name. If this succeeds, we're done.
    std::error_code EC = tWriter->acquire();
    if (!EC) {
      // Acquire
      Writer = std::move(tWriter);
      return;
    }

    if (EC != errc::file_exists) {
      std::string S("failed to create link ");
      raw_string_ostream OSS(S);
      OSS << LockFileName.str();
      setError(EC, OSS.str());
      return;
    }

    // Someone else managed to create the lock file first. Read the process ID
    // from the lock file.
    if ((Reader = LockFileReader::subscribe(LockFileName)))
      return;

    if (!sys::fs::exists(LockFileName)) {
      // The previous owner released the lock file before we could read it.
      // Try to get ownership again.
      continue;
    }

    // There is a lock file that nobody owns; try to clean it up and get
    // ownership.
    if ((EC = sys::fs::remove(LockFileName))) {
      std::string S("failed to remove lockfile ");
      S.append(std::string(LockFileName));
      setError(EC, S);
      return;
    }
  }
}

LockFileManager::LockFileState LockFileManager::getState() const {
  if (Reader)
    return LFS_Shared;

  if (ErrorCode)
    return LFS_Error;

  return LFS_Owned;
}

std::string LockFileManager::getErrorMessage() const {
  if (ErrorCode) {
    std::string Str(ErrorDiagMsg);
    std::string ErrCodeMsg = ErrorCode.message();
    raw_string_ostream OSS(Str);
    if (!ErrCodeMsg.empty())
      OSS << ": " << ErrCodeMsg;
    return OSS.str();
  }
  return "";
}

LockFileManager::~LockFileManager() {
#if 0
  if (Writer)
    sys::fs::remove(LockFileName);
#endif
}

LockFileWriter::~LockFileWriter() {
  if (Acquired) {
#if 1
    char linkpath[PATH_MAX];
    ::readlink(LockFileName.str().c_str(), linkpath, sizeof(linkpath));
#endif
    sys::fs::remove(LockFileName);
  }
  if (!UniqueLockFileName.empty())
    ::unlink(UniqueLockFileName.c_str());
  if (UniquePipeFD > 0) {
    fprintf(stderr, "%d\t[~UNLINK]%d\t%s\n", ::getpid(), UniquePipeFD,
            UniqueLockFileName.c_str());
    ::close(UniquePipeFD);
  }

  // The unique file is now gone, so remove it from the signal handler. This
  // matches a sys::RemoveFileOnSignal() in LockFileManager().
  sys::DontRemoveFileOnSignal(UniqueLockFileName);
}

std::error_code LockFileWriter::acquire() {
  // Create a link from the lock file name. If this succeeds, we're done.
  std::error_code EC = sys::fs::create_link(UniqueLockFileName, LockFileName);

  if (!EC) {
    fprintf(stderr, "%d\t[LOCK  ]%d\t%s\n", ::getpid(), UniquePipeFD,
            UniqueLockFileName.c_str());
    Acquired = true;
    return EC;
  }

  return EC;
}

LockFileManager::WaitForUnlockResult
LockFileManager::waitForUnlock(const unsigned MaxSeconds) {
  if (getState() != LFS_Shared)
    return Res_Success;

  // Since we don't yet have an event-based method to wait for the lock file,
  // implement randomized exponential backoff, similar to Ethernet collision
  // algorithm. This improves performance on machines with high core counts
  // when the file lock is heavily contended by multiple clang processes
  const unsigned long MinWaitDurationMS = 10;
  const unsigned long MaxWaitMultiplier = 50; // 500ms max wait
  unsigned long WaitMultiplier = 1;
  unsigned long ElapsedTimeSeconds = 0;

  std::random_device Device;
  std::default_random_engine Engine(Device());

  auto StartTime = std::chrono::steady_clock::now();

  do {
    // FIXME: implement event-based waiting

    // Sleep for the designated interval, to allow the owning process time to
    // finish up and remove the lock file.
    std::uniform_int_distribution<unsigned long> Distribution(1,
                                                              WaitMultiplier);
    unsigned long WaitDurationMS = MinWaitDurationMS * Distribution(Engine);
#if 1
    {
      char linkpath[PATH_MAX];
      ::readlink(LockFileName.c_str(), linkpath, sizeof(linkpath));
    }
#endif
    Reader->Wait(WaitDurationMS);

    if (sys::fs::access(LockFileName.c_str(), sys::fs::AccessMode::Exist) ==
        errc::no_such_file_or_directory) {
      // If the original file wasn't created, somone thought the lock was dead.
      if (!sys::fs::exists(FileName))
        return Res_OwnerDied;
      return Res_Success;
    }

    // If the process owning the lock died without cleaning up, just bail out.
    if (!Reader->processStillExecuting())
      return Res_OwnerDied;

    WaitMultiplier *= 2;
    if (WaitMultiplier > MaxWaitMultiplier) {
      WaitMultiplier = MaxWaitMultiplier;
    }

    ElapsedTimeSeconds = std::chrono::duration_cast<std::chrono::seconds>(
                             std::chrono::steady_clock::now() - StartTime)
                             .count();

  } while (ElapsedTimeSeconds < MaxSeconds);

  // Give up.
  return Res_Timeout;
}

std::error_code LockFileManager::unsafeRemoveLockFile() {
  return sys::fs::remove(LockFileName);
}
