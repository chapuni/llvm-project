#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-cde-builtin-aliases",
                     cl::desc("Generate list of valid ARM CDE builtin aliases for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitCdeBuiltinAliases); }));
} // end anonymous namespace
