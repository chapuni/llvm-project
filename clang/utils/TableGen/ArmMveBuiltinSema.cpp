#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-mve-builtin-sema",
                     cl::desc("Generate ARM MVE builtin sema checks for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitMveBuiltinSema); }));
} // end anonymous namespace
