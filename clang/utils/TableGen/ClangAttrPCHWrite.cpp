#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-pch-write",
                     cl::desc("Generate clang PCH attribute writer"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrPCHWrite); }));
} // end anonymous namespace
