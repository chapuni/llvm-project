#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-neon-sema",
                     cl::desc("Generate ARM NEON sema support for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitNeonSema); }));
} // end anonymous namespace
