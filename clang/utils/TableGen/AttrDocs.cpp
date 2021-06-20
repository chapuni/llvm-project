#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-attr-docs",
                     cl::desc("Generate attribute documentation"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrDocs); }));
} // end anonymous namespace
