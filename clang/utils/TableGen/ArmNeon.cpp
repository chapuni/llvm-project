#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-neon",
                     cl::desc("Generate arm_neon.h for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitNeon); }));
} // end anonymous namespace
