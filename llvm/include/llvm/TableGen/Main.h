//===- llvm/TableGen/Main.h - tblgen entry point ----------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the common entry point for tblgen tools.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TABLEGEN_MAIN_H
#define LLVM_TABLEGEN_MAIN_H

#include "llvm/Support/CommandLine.h"

namespace llvm {

class raw_ostream;
class RecordKeeper;

/// Perform the action using Records, and write output to OS.
/// Returns true on error, false otherwise.
using TableGenMainFn = int (raw_ostream &OS, RecordKeeper &Records);

/// FIXME: FIXME
using TableGenActionFn = void (RecordKeeper &Records, raw_ostream &OS);

namespace TableGen {
extern void RegisterAction(TableGenActionFn *ActionFn);
extern void ParseCommandLineOptions(int argc, char **argv);

class Action : public cl::opt<bool> {
public:
  Action(TableGenActionFn EmitterFn, StringRef name, StringRef desc)
      : cl::opt<bool>(name, cl::desc(desc)) {
    setCallback(
        [EmitterFn](const bool &) { TableGen::RegisterAction(EmitterFn); });
  }
};

template <class EmitterTy> class EmitterAction : public Action {
private:
  static void CB2(RecordKeeper &RK, raw_ostream &OS) { EmitterTy(RK).run(OS); }

public:
  EmitterAction(StringRef name, StringRef desc) : Action(CB2, name, desc) {}
};

} // end namespace TableGen

int TableGenMain(const char *argv0, TableGenMainFn *MainFn);

} // end namespace llvm

#endif // LLVM_TABLEGEN_MAIN_H
