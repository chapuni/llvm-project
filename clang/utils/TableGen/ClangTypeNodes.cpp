#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-type-nodes",
                     cl::desc("Generate Clang AST type nodes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangTypeNodes); }));
} // end anonymous namespace
