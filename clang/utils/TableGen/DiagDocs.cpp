#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-diag-docs",
                     cl::desc("Generate diagnostic documentation"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangDiagDocs); }));
} // end anonymous namespace
