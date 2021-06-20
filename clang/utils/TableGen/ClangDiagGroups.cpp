#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangDiagGroups, "gen-clang-diag-groups",
                        "Generate Clang diagnostic groups");
}
