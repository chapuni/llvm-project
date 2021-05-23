#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitSveRangeChecks,
                        "gen-arm-sve-sema-rangechecks",
                        "Generate arm_sve_sema_rangechecks.inc for clang");
}
