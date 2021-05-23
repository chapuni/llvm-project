#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-cde-builtin-def",
                     cl::desc("Generate ARM CDE builtin definitions for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitCdeBuiltinDef); }));
} // end anonymous namespace
