#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-data-collectors",
                     cl::desc("Generate data collectors for AST nodes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangDataCollectors); }));
} // end anonymous namespace
