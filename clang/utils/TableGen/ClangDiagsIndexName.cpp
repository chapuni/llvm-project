#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-diags-index-name",
                     cl::desc("Generate Clang diagnostic name index"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangDiagsIndexName); }));
} // end anonymous namespace
