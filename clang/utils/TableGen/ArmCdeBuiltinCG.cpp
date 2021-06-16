#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-cde-builtin-codegen",
                     cl::desc("Generate ARM CDE builtin code-generator for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitCdeBuiltinCG); }));
} // end anonymous namespace
