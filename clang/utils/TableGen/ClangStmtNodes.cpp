#include "TableGenBackends.h"
#include "ASTTableGen.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
void EmitClangStmtNodes(RecordKeeper &Records, raw_ostream &OS) {
  EmitClangASTNodes(Records, OS, StmtNodeClassName, "");
}

cl::opt<bool> Action("gen-clang-stmt-nodes",
                     cl::desc("Generate Clang AST statement nodes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangStmtNodes); }));
} // end anonymous namespace
