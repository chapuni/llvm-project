#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrImpl, "gen-clang-attr-impl",
                        "Generate clang attribute implementations");
}
