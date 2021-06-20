#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-parsed-attr-list",
                     cl::desc("Generate a clang parsed attribute list"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrParsedAttrList); }));
} // end anonymous namespace
