#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-cde-header",
                     cl::desc("Generate arm_cde.h for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitCdeHeader); }));
} // end anonymous namespace
