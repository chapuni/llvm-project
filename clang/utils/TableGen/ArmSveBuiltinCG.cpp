#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitSveBuiltinCG, "gen-arm-sve-builtin-codegen",
                        "Generate arm_sve_builtin_cg_map.inc for clang");
}
