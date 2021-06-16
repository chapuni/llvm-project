#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-sve-typeflags",
                     cl::desc("Generate arm_sve_typeflags.inc for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitSveTypeFlags); }));
} // end anonymous namespace
