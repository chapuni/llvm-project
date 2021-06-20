#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitMveBuiltinCG, "gen-arm-mve-builtin-codegen",
                        "Generate ARM MVE builtin code-generator for clang");
}
