#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitMveHeader, "gen-arm-mve-header",
                        "Generate arm_mve.h for clang");
}
