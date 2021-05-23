#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-neon-test",
                     cl::desc("Generate ARM NEON tests for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitNeonTest); }));
} // end anonymous namespace
