#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-sve-builtin-codegen",
                     cl::desc("Generate arm_sve_builtin_cg_map.inc for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitSveBuiltinCG); }));
} // end anonymous namespace
