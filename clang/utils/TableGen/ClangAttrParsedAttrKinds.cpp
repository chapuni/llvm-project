#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-parsed-attr-kinds",
                     cl::desc("Generate a clang parsed attribute kinds"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrParsedAttrKinds); }));
} // end anonymous namespace
