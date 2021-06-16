#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-syntax-node-classes",
                     cl::desc("Generate definitions of Clang Syntax Tree node clasess"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangSyntaxNodeClasses); }));
} // end anonymous namespace
