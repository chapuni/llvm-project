#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-template-instantiate",
                     cl::desc("Generate a clang template instantiate code"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrTemplateInstantiate); }));
} // end anonymous namespace
