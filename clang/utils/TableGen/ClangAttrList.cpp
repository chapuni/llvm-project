#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-list",
                     cl::desc("Generate a clang attribute list"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrList); }));
} // end anonymous namespace
