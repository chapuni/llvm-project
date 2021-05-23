#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrList, "gen-clang-attr-list",
                        "Generate a clang attribute list");
}
