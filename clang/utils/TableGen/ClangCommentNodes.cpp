#include "TableGenBackends.h"
#include "ASTTableGen.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
void EmitClangCommentNodes(RecordKeeper &Records, raw_ostream &OS) {
  EmitClangASTNodes(Records, OS, CommentNodeClassName, "");
}

cl::opt<bool> Action("gen-clang-comment-nodes",
                     cl::desc("Generate Clang AST comment nodes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangCommentNodes); }));
} // end anonymous namespace
