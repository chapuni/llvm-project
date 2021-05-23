#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangTypeWriter, "gen-clang-type-writer",
                        "Generate Clang AbstractTypeWriter class");
}
