//===- IntrinsicEmitter.cpp - Generate intrinsic information --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This tablegen backend emits information about intrinsic functions.
//
//===----------------------------------------------------------------------===//

#include "CodeGenIntrinsics.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Error.h"
#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/TableGenBackend.h"
using namespace llvm;

namespace {

cl::OptionCategory GenIntrinsicCat("Options for -gen-intrinsic-enums");
cl::opt<std::string>
    IntrinsicPrefix("intrinsic-prefix",
                    cl::desc("Generate intrinsics with this target prefix"),
                    cl::value_desc("target prefix"), cl::cat(GenIntrinsicCat));

class IntrinsicEmitter {
  RecordKeeper &Records;

public:
  IntrinsicEmitter(RecordKeeper &R) : Records(R) {}

  void run(raw_ostream &OS);

  void EmitEnumInfo(const CodeGenIntrinsicTable &Ints, raw_ostream &OS);
};

//===----------------------------------------------------------------------===//
// IntrinsicEmitter Implementation
//===----------------------------------------------------------------------===//

void IntrinsicEmitter::run(raw_ostream &OS) {
  emitSourceFileHeader("Intrinsic Function Source Fragment", OS);

  CodeGenIntrinsicTable Ints(Records);

  // Emit the enum information.
  EmitEnumInfo(Ints, OS);
}

void IntrinsicEmitter::EmitEnumInfo(const CodeGenIntrinsicTable &Ints,
                                    raw_ostream &OS) {
  // Find the TargetSet for which to generate enums. There will be an initial
  // set with an empty target prefix which will include target independent
  // intrinsics like dbg.value.
  const CodeGenIntrinsicTable::TargetSet *Set = nullptr;
  for (const auto &Target : Ints.Targets) {
    if (Target.Name == IntrinsicPrefix) {
      Set = &Target;
      break;
    }
  }
  if (!Set) {
    std::vector<std::string> KnownTargets;
    for (const auto &Target : Ints.Targets)
      if (!Target.Name.empty())
        KnownTargets.push_back(Target.Name);
    PrintFatalError("tried to generate intrinsics for unknown target " +
                    IntrinsicPrefix +
                    "\nKnown targets are: " + join(KnownTargets, ", ") + "\n");
  }

  // Generate a complete header for target specific intrinsics.
  if (!IntrinsicPrefix.empty()) {
    std::string UpperPrefix = StringRef(IntrinsicPrefix).upper();
    OS << "#ifndef LLVM_IR_INTRINSIC_" << UpperPrefix << "_ENUMS_H\n";
    OS << "#define LLVM_IR_INTRINSIC_" << UpperPrefix << "_ENUMS_H\n\n";
    OS << "namespace llvm {\n";
    OS << "namespace Intrinsic {\n";
    OS << "enum " << UpperPrefix << "Intrinsics : unsigned {\n";
  }

  OS << "// Enum values for intrinsics\n";
  for (unsigned i = Set->Offset, e = Set->Offset + Set->Count; i != e; ++i) {
    OS << "    " << Ints[i].EnumName;

    // Assign a value to the first intrinsic in this target set so that all
    // intrinsic ids are distinct.
    if (i == Set->Offset)
      OS << " = " << (Set->Offset + 1);

    OS << ", ";
    if (Ints[i].EnumName.size() < 40)
      OS.indent(40 - Ints[i].EnumName.size());
    OS << " // " << Ints[i].Name << "\n";
  }

  // Emit num_intrinsics into the target neutral enum.
  if (IntrinsicPrefix.empty()) {
    OS << "    num_intrinsics = " << (Ints.size() + 1) << "\n";
  } else {
    OS << "}; // enum\n";
    OS << "} // namespace Intrinsic\n";
    OS << "} // namespace llvm\n\n";
    OS << "#endif\n";
  }
}

TableGen::EmitterAction<IntrinsicEmitter> Action("gen-intrinsic-enums",
                                                 "Generate intrinsic enums");

} // namespace
