#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitCdeBuiltinCG, "gen-arm-cde-builtin-codegen",
                        "Generate ARM CDE builtin code-generator for clang");
}
