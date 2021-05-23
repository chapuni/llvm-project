#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrPCHRead, "gen-clang-attr-pch-read",
                        "Generate clang PCH attribute reader");
}
