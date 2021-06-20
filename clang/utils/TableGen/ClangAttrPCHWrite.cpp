#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrPCHWrite,
                        "gen-clang-attr-pch-write",
                        "Generate clang PCH attribute writer");
}
