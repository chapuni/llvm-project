#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-opcodes",
                     cl::desc("Generate Clang constexpr interpreter opcodes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangOpcodes); }));
} // end anonymous namespace
