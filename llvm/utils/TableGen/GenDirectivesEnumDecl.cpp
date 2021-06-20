#include "TableGenBackends.h" // Declares all backends.
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
cl::opt<bool> Action("gen-directive-decl",
                     cl::desc("Generate directive related declaration code (header file)"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitDirectivesDecl); }));
} // end anonymous namespace
