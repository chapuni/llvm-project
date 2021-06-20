#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-basic-writer",
                     cl::desc("Generate Clang BasicWriter classes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangBasicWriter); }));
} // end anonymous namespace
