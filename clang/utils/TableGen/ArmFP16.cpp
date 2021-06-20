#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitFP16, "gen-arm-fp16",
                        "Generate arm_fp16.h for clang");
}
