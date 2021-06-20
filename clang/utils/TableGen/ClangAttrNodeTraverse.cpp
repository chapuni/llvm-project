#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrNodeTraverse,
                        "gen-clang-attr-node-traverse",
                        "Generate clang attribute traverser");
}
