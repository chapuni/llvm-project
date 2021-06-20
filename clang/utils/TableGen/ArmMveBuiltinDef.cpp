#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitMveBuiltinDef, "gen-arm-mve-builtin-def",
                        "Generate ARM MVE builtin definitions for clang");
}
