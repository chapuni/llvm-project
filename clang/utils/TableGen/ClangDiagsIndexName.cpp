#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangDiagsIndexName,
                        "gen-clang-diags-index-name",
                        "Generate Clang diagnostic name index");
}
