#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitSveBuiltins, "gen-arm-sve-builtins",
                        "Generate arm_sve_builtins.inc for clang");
}
