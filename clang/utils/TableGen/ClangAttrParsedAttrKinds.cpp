#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrParsedAttrKinds,
                        "gen-clang-attr-parsed-attr-kinds",
                        "Generate a clang parsed attribute kinds");
}
