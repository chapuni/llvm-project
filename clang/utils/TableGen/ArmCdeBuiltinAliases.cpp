#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action
    Action(clang::EmitCdeBuiltinAliases, "gen-arm-cde-builtin-aliases",
           "Generate list of valid ARM CDE builtin aliases for clang");
}
