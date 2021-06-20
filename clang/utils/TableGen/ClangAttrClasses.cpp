#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-classes",
                     cl::desc("Generate clang attribute clases"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrClass); }));
} // end anonymous namespace
