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

#if defined(__APPLE__) && defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ > 1050)
#define USE_OSX_GETHOSTUUID 1
#else
#define USE_OSX_GETHOSTUUID 0
#endif

#if USE_OSX_GETHOSTUUID
#include <uuid/uuid.h>
#endif

using namespace llvm;

#if 0
class LockFileReader {
  SmallString<256> UniquePipeName;
  SmallString<256> UniqueLockFileName;

  LockFileReader() = delete;
  LockFileReader(StringRef LockFileName);

public:
  std::unique_ptr<LockFileReader> Subscribe(StringRef LockFileName) {
    return std::make_unique(new LockFileReader(LockFileName));
  }
};
#endif

/// Attempt to read the lock file with the given name, if it exists.
///
/// \param LockFileName The name of the lock file to read.
///
/// \returns The process ID of the process that owns this lock file
Optional<std::pair<std::string, int> >
LockFileManager::readLockFile(StringRef LockFileName) {
  char linkpath[PATH_MAX];
  ssize_t linkpathlen;
  SmallString<256> uniqpipename;
  SmallString<256> uniqlockname;
  std::unique_ptr<MemoryBuffer> MBP;
  int fd;

  // Read the owning host and PID out of the lock file. If it appears that the
  // owning process is dead, the lock file is invalid.
  while (1) {
    linkpathlen = ::readlink(LockFileName.str().c_str(), linkpath, sizeof(linkpath));
    if (linkpathlen <= 0) {
      // error
      if (!uniqlockname.empty())
        fprintf(stderr, "%d\t[FAILED](%zd)\t%s\n", ::getpid(), linkpathlen, LockFileName.str().c_str());
      sys::fs::remove(LockFileName);
      return None;
    }

    linkpath[linkpathlen] = 0;
    if (uniqlockname != linkpath) {
      if (!uniqpipename.empty())
        fprintf(stderr, "%d\t[---]\t%s\n\t[+++]\t%s\n", ::getpid(), uniqpipename.c_str(), linkpath);
      uniqpipename = linkpath;
      uniqpipename += ".pipe";
      uniqlockname = linkpath;
    }

    fd = ::open(uniqpipename.c_str(), O_RDONLY | O_NONBLOCK);
    ErrorOr<std::unique_ptr<MemoryBuffer>> MBOrErr = MemoryBuffer::getFile(uniqlockname);
    if (fd > 0 && MBOrErr) {
      MBP = std::move(MBOrErr.get());
      break;
    }

    if (fd > 0)
      ::close(fd);
  }

  MemoryBuffer &MB = *MBP.get();

  StringRef Hostname;
  StringRef PIDStr;
#if 1
  SmallVector<StringRef, 4> toks;
  SplitString(MB.getBuffer(), toks, "#");
  Hostname = toks[1];
  PIDStr = toks[2];
#else
  std::tie(Hostname, PIDStr) = getToken(MB.getBuffer(), "#");
  fprintf(stderr, "<%s><%s>\n", Hostname.str().c_str(), PIDStr.str().c_str());
  PIDStr = PIDStr.substr(PIDStr.find_first_not_of("#"));
#endif
  int PID;
  if (!PIDStr.getAsInteger(10, PID)) {
    auto Owner = std::make_pair(std::string(Hostname), PID);
    if (processStillExecuting(Owner.first, Owner.second)) {
      if (UniquePipeFD > 0) {
        fprintf(stderr, "%d\t[close]%d\t%s\n\t[reOPENRD]%d\t%s\n", ::getpid(), UniquePipeFD, UniquePipeName.c_str(), fd, uniqpipename.c_str());
        ::close(UniquePipeFD);
      } else {
        fprintf(stderr, "%d\t[OPENRD]%d\t%s\n", ::getpid(), fd, uniqpipename.c_str());
      }
      UniquePipeName = uniqpipename;
      UniqueLockFileName = uniqlockname;
      UniquePipeFD = fd;
      return Owner;
    }
  }

  // Delete the lock file. It's invalid anyway.
  sys::fs::remove(LockFileName);
  return None;
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

bool LockFileManager::processStillExecuting(StringRef HostID, int PID) {
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

namespace {

/// An RAII helper object ensure that the unique lock file is removed.
///
/// Ensures that if there is an error or a signal before we finish acquiring the
/// lock, the unique file will be removed. And if we successfully take the lock,
/// the signal handler is left in place so that signals while the lock is held
/// will remove the unique lock file. The caller should ensure there is a
/// matching call to sys::DontRemoveFileOnSignal when the lock is released.
class RemoveUniqueLockFileOnSignal {
  SmallString<256> Filename;
  bool RemoveImmediately;
public:
  RemoveUniqueLockFileOnSignal(StringRef Name)
  : Filename(Name), RemoveImmediately(true) {
    sys::RemoveFileOnSignal(Filename, nullptr);
  }

  ~RemoveUniqueLockFileOnSignal() {
    if (!RemoveImmediately) {
      // Leave the signal handler enabled. It will be removed when the lock is
      // released.
      return;
    }
    ::unlink(Filename.c_str());
    fprintf(stderr, "%d\t[remove]\t%s\n", ::getpid(), Filename.c_str());
    sys::DontRemoveFileOnSignal(Filename);
  }

  void lockAcquired() { RemoveImmediately = false; }
};

} // end anonymous namespace

LockFileManager::LockFileManager(StringRef FileName)
{
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
  if ((Owner = readLockFile(LockFileName)))
    return;

  std::string LockFileID;
  if (auto EC = getLockFileID(LockFileID)) {
    setError(EC, "failed to get host id");
    return;
  }

  // Create a lock file that is unique to this instance.
  UniqueLockFileName = LockFileName;
  UniqueLockFileName += LockFileID;
  UniqueLockFileName += "-%%%%%%%%";
  int UniqueLockFileID;
  if (std::error_code EC = sys::fs::createUniqueFile(
          UniqueLockFileName, UniqueLockFileID, UniqueLockFileName)) {
    std::string S("failed to create unique file ");
    S.append(std::string(UniqueLockFileName.str()));
    setError(EC, S);
    return;
  }

  // Write our process ID to our unique lock file.
  {
    SmallString<256> HostID;
    if (auto EC = getHostID(HostID)) {
      setError(EC, "failed to get host id");
      return;
    }

    raw_fd_ostream Out(UniqueLockFileID, /*shouldClose=*/true);
    Out << ".#" << HostID << '#' << sys::Process::getProcessId() << '#';
    Out.close();

    if (Out.has_error()) {
      // We failed to write out PID, so report the error, remove the
      // unique lock file, and fail.
      std::string S("failed to write to ");
      S.append(std::string(UniqueLockFileName.str()));
      setError(Out.error(), S);
      sys::fs::remove(UniqueLockFileName);
      return;
    }
  }

  // Clean up the unique file on signal, which also releases the lock if it is
  // held since the .lock symlink will point to a nonexistent file.
  RemoveUniqueLockFileOnSignal RemoveUniqueFile(UniqueLockFileName);

#if 1
  UniquePipeName = UniqueLockFileName;
  UniquePipeName += ".pipe";
  RemoveUniqueLockFileOnSignal RemoveUniquePipe(UniquePipeName);
  if (::mkfifo(UniquePipeName.c_str(), 0666) == 0) {
    int rfd = ::open(UniquePipeName.c_str(), O_RDONLY | O_NONBLOCK);
    if (rfd > 0) {
      UniquePipeFD = ::open(UniquePipeName.c_str(), O_WRONLY | O_NONBLOCK);
      if (UniquePipeFD > 0) {
      } else {
        ::close(rfd);
      }
    }
    fprintf(stderr, "%d\t[OPENWR]%d\t%s\n", ::getpid(), UniquePipeFD, UniquePipeName.c_str());
  }
#endif

  while (true) {
    // Create a link from the lock file name. If this succeeds, we're done.
    std::error_code EC =
        sys::fs::create_link(UniqueLockFileName, LockFileName);
    if (!EC) {
      RemoveUniqueFile.lockAcquired();
      RemoveUniquePipe.lockAcquired();
      fprintf(stderr, "%d\t[LOCK  ]%d\t%s\n", ::getpid(), UniquePipeFD, UniquePipeName.c_str());
      return;
    }

    if (EC != errc::file_exists) {
      std::string S("failed to create link ");
      raw_string_ostream OSS(S);
      OSS << LockFileName.str() << " to " << UniqueLockFileName.str();
      setError(EC, OSS.str());
      return;
    }

    // Someone else managed to create the lock file first. Read the process ID
    // from the lock file.
    if ((Owner = readLockFile(LockFileName))) {
      // Wipe out our unique lock file (it's useless now)
      return;
    }

    if (!sys::fs::exists(LockFileName)) {
      // The previous owner released the lock file before we could read it.
      // Try to get ownership again.
      continue;
    }

    // There is a lock file that nobody owns; try to clean it up and get
    // ownership.
    if ((EC = sys::fs::remove(LockFileName))) {
      std::string S("failed to remove lockfile ");
      S.append(std::string(UniqueLockFileName.str()));
      setError(EC, S);
      return;
    }
  }
}

LockFileManager::LockFileState LockFileManager::getState() const {
  if (Owner)
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
  if (getState() != LFS_Owned) {
#if 1
    if (UniquePipeFD > 0) {
      fprintf(stderr, "%d\t[~CLOSE]%d\t%s\n", ::getpid(), UniquePipeFD, UniquePipeName.c_str());
      ::close(UniquePipeFD);
    }
#endif
    return;
  }

  // Since we own the lock, remove the lock file and our own unique lock file.
  sys::fs::remove(LockFileName);
  sys::fs::remove(UniqueLockFileName);
#if 1
  if (UniquePipeFD > 0) {
    ::unlink(UniquePipeName.c_str());
    fprintf(stderr, "%d\t[~UNLINK]%d\t%s\n", ::getpid(), UniquePipeFD, UniquePipeName.c_str());
    ::close(UniquePipeFD);
  }
#endif
  // The unique file is now gone, so remove it from the signal handler. This
  // matches a sys::RemoveFileOnSignal() in LockFileManager().
  sys::DontRemoveFileOnSignal(UniqueLockFileName);
  sys::DontRemoveFileOnSignal(UniquePipeName);
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

  struct pollfd fds[1];
  fds[0].fd = UniquePipeFD;
  fds[0].events = POLLIN;

  do {
    // FIXME: implement event-based waiting

    // Sleep for the designated interval, to allow the owning process time to
    // finish up and remove the lock file.
    std::uniform_int_distribution<unsigned long> Distribution(1,
                                                              WaitMultiplier);
    unsigned long WaitDurationMS = MinWaitDurationMS * Distribution(Engine);
    if (UniquePipeFD > 0) {
      int r = ::poll(fds, 1, WaitDurationMS);
      if (r == 1 && (fds[0].revents & POLLHUP)) {
        ::close(UniquePipeFD);
        fprintf(stderr, "%d\t[+ ACCLOSE]%d\t%s\n", ::getpid(), UniquePipeFD, UniquePipeName.c_str());
        UniquePipeFD = -1;
      }
    } else {
      fprintf(stderr, "%d [WAIT]\t\t\t%s\n", ::getpid(), LockFileName.c_str());
      std::this_thread::sleep_for(std::chrono::milliseconds(WaitDurationMS));
    }

    if (sys::fs::access(LockFileName.c_str(), sys::fs::AccessMode::Exist) ==
        errc::no_such_file_or_directory) {
      // If the original file wasn't created, somone thought the lock was dead.
      if (!sys::fs::exists(FileName))
        return Res_OwnerDied;
      return Res_Success;
    }

    // If the process owning the lock died without cleaning up, just bail out.
    if (!processStillExecuting((*Owner).first, (*Owner).second))
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
