#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-parsed-attr-impl",
                     cl::desc("Generate the clang parsed attribute helpers"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrParsedAttrImpl); }));
} // end anonymous namespace
