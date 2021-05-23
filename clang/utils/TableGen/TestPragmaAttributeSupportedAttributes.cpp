#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-test-pragma-attribute-supported-attributes",
                     cl::desc("Generate a list of attributes supported by #pragma clang "
                              "attribute for testing purposes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitTestPragmaAttributeSupportedAttributes); }));
} // end anonymous namespace
