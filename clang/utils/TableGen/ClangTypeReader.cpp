#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-type-reader",
                     cl::desc("Generate Clang AbstractTypeReader class"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangTypeReader); }));
} // end anonymous namespace
