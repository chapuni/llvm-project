#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-basic-reader",
                     cl::desc("Generate Clang BasicReader classes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangBasicReader); }));
} // end anonymous namespace
