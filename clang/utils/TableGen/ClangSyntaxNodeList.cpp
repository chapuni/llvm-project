#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-syntax-node-list",
                     cl::desc("Generate list of Clang Syntax Tree node types"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangSyntaxNodeList); }));
} // end anonymous namespace
