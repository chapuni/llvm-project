#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-ast-visitor",
                     cl::desc("Generate a recursive AST visitor for clang attributes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrASTVisitor); }));
} // end anonymous namespace
