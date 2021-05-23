#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitSveHeader, "gen-arm-sve-header",
                        "Generate arm_sve.h for clang");
}
