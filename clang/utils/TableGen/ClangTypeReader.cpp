#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangTypeReader, "gen-clang-type-reader",
                        "Generate Clang AbstractTypeReader class");
}
