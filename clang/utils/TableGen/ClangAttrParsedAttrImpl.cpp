#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrParsedAttrImpl,
                        "gen-clang-attr-parsed-attr-impl",
                        "Generate the clang parsed attribute helpers");
}
