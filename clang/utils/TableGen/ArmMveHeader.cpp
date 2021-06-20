#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-mve-header",
                     cl::desc("Generate arm_mve.h for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitMveHeader); }));
} // end anonymous namespace
