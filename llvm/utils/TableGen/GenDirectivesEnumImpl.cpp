#include "TableGenBackends.h" // Declares all backends.
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
cl::opt<bool> Action("gen-directive-impl",
                     cl::desc("Generate directive related implementation code"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitDirectivesImpl); }));
} // end anonymous namespace
