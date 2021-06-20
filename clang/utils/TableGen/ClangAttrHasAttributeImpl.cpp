#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrHasAttrImpl,
                        "gen-clang-attr-has-attribute-impl",
                        "Generate a clang attribute spelling list");
}
