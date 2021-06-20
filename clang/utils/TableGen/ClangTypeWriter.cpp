#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-type-writer",
                     cl::desc("Generate Clang AbstractTypeWriter class"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangTypeWriter); }));
} // end anonymous namespace
