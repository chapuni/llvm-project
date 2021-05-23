#include "ASTTableGen.h"
#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
void EmitClangCommentNodes(RecordKeeper &Records, raw_ostream &OS) {
  EmitClangASTNodes(Records, OS, CommentNodeClassName, "");
}

TableGen::Action Action(EmitClangCommentNodes, "gen-clang-comment-nodes",
                        "Generate Clang AST comment nodes");
} // namespace
