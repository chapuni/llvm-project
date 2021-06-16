#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-arm-sve-sema-rangechecks",
                     cl::desc("Generate arm_sve_sema_rangechecks.inc for clang"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitSveRangeChecks); }));
} // end anonymous namespace
