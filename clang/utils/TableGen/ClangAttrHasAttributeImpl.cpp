#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-has-attribute-impl",
                     cl::desc("Generate a clang attribute spelling list"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrHasAttrImpl); }));
} // end anonymous namespace
