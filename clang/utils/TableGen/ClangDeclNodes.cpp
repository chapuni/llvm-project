#include "ASTTableGen.h"
#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
void EmitClangDeclNodes(RecordKeeper &Records, raw_ostream &OS) {
  EmitClangASTNodes(Records, OS, DeclNodeClassName, "Decl");
  EmitClangDeclContext(Records, OS);
}

TableGen::Action Action(EmitClangDeclNodes, "gen-clang-decl-nodes",
                        "Generate Clang AST declaration nodes");
} // namespace
