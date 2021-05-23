#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangDiagDocs, "gen-diag-docs",
                        "Generate diagnostic documentation");
}
