#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrSpellingListIndex,
                        "gen-clang-attr-spelling-index",
                        "Generate a clang attribute spelling index");
}
