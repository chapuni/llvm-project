#include "ASTTableGen.h"
#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
void EmitClangStmtNodes(RecordKeeper &Records, raw_ostream &OS) {
  EmitClangASTNodes(Records, OS, StmtNodeClassName, "");
}

TableGen::Action Action(EmitClangStmtNodes, "gen-clang-stmt-nodes",
                        "Generate Clang AST statement nodes");
} // namespace
