#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-text-node-dump",
                     cl::desc("Generate clang attribute text node dumper"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrTextNodeDump); }));
} // end anonymous namespace
