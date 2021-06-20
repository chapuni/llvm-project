#include "TableGenBackends.h"
#include "ASTTableGen.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
void EmitClangDeclNodes(RecordKeeper &Records, raw_ostream &OS) {
  EmitClangASTNodes(Records, OS, DeclNodeClassName, "Decl");
  EmitClangDeclContext(Records, OS);
}

cl::opt<bool> Action("gen-clang-decl-nodes",
                     cl::desc("Generate Clang AST declaration nodes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangDeclNodes); }));
} // end anonymous namespace
