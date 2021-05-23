#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitCdeHeader, "gen-arm-cde-header",
                        "Generate arm_cde.h for clang");
}
