#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-opt-docs",
                     cl::desc("Generate option documentation"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangOptDocs); }));
} // end anonymous namespace
