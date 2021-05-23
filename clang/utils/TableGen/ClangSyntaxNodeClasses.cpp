#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action
    Action(clang::EmitClangSyntaxNodeClasses, "gen-clang-syntax-node-classes",
           "Generate definitions of Clang Syntax Tree node clasess");
}
