#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrTextNodeDump,
                        "gen-clang-attr-text-node-dump",
                        "Generate clang attribute text node dumper");
}
