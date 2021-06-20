#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitCdeBuiltinSema, "gen-arm-cde-builtin-sema",
                        "Generate ARM CDE builtin sema checks for clang");
}
