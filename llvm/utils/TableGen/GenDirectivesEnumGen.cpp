#include "TableGenBackends.h" // Declares all backends.
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
cl::opt<bool> Action("gen-directive-gen",
                     cl::desc("Generate directive related implementation code part"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitDirectivesGen); }));
} // end anonymous namespace
