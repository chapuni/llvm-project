#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-mve-builtin-def",
                     cl::desc("Generate ARM MVE builtin definitions for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitMveBuiltinDef); }));
} // end anonymous namespace
