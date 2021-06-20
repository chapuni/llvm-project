#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-pch-read",
                     cl::desc("Generate clang PCH attribute reader"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrPCHRead); }));
} // end anonymous namespace
