#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-sve-header",
                     cl::desc("Generate arm_sve.h for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitSveHeader); }));
} // end anonymous namespace
