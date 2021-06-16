#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-bf16",
                     cl::desc("Generate arm_bf16.h for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitBF16); }));
} // end anonymous namespace
