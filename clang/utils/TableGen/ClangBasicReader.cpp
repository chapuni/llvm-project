#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangBasicReader, "gen-clang-basic-reader",
                        "Generate Clang BasicReader classes");
}
