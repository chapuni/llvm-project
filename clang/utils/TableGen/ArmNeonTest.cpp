#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitNeonTest, "gen-arm-neon-test",
                        "Generate ARM NEON tests for clang");
}
