#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-diag-groups",
                     cl::desc("Generate Clang diagnostic groups"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangDiagGroups); }));
} // end anonymous namespace
