#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-opencl-builtins",
                     cl::desc("Generate OpenCL builtin declaration handlers"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrClass); }));
} // end anonymous namespace
