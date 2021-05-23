#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangBasicWriter, "gen-clang-basic-writer",
                        "Generate Clang BasicWriter classes");
}
