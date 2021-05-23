#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitNeon, "gen-arm-neon",
                        "Generate arm_neon.h for clang");
}
