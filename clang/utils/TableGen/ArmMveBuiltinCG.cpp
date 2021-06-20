#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-mve-builtin-codegen",
                     cl::desc("Generate ARM MVE builtin code-generator for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitMveBuiltinCG); }));
} // end anonymous namespace
