#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitMveBuiltinSema, "gen-arm-mve-builtin-sema",
                        "Generate ARM MVE builtin sema checks for clang");
}
