#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitCdeBuiltinDef, "gen-arm-cde-builtin-def",
                        "Generate ARM CDE builtin definitions for clang");
}
