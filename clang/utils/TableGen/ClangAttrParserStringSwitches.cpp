#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-parser-string-switches",
                     cl::desc("Generate all parser-related attribute string switches"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrParserStringSwitches); }));
} // end anonymous namespace
