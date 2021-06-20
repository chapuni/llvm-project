#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrParsedAttrList,
                        "gen-clang-attr-parsed-attr-list",
                        "Generate a clang parsed attribute list");
}
