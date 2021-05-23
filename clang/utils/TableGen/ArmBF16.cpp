#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitBF16, "gen-arm-bf16",
                        "Generate arm_bf16.h for clang");
}
