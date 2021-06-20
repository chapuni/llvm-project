#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action
    Action(clang::EmitMveBuiltinAliases, "gen-arm-mve-builtin-aliases",
           "Generate list of valid ARM MVE builtin aliases for clang");
}
