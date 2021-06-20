#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitNeonSema, "gen-arm-neon-sema",
                        "Generate ARM NEON sema support for clang");
}
