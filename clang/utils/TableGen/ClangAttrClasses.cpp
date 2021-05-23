#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrClass, "gen-clang-attr-classes",
                        "Generate clang attribute clases");
}
