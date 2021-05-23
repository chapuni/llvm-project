#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-sa-checkers",
                     cl::desc("Generate Clang Static Analyzer checkers"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangSACheckers); }));
} // end anonymous namespace
