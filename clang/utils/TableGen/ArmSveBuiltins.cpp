#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-sve-builtins",
                     cl::desc("Generate arm_sve_builtins.inc for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitSveBuiltins); }));
} // end anonymous namespace
