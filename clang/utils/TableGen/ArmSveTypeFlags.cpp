#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitSveTypeFlags, "gen-arm-sve-typeflags",
                        "Generate arm_sve_typeflags.inc for clang");
}
