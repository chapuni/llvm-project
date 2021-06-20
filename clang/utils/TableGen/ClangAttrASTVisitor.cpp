#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action
    Action(clang::EmitClangAttrASTVisitor, "gen-clang-attr-ast-visitor",
           "Generate a recursive AST visitor for clang attributes");
}
