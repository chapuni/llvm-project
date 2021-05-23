#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-impl",
                     cl::desc("Generate clang attribute implementations"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrImpl); }));
} // end anonymous namespace
