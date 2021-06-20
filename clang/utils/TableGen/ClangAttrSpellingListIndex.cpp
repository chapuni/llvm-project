#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-spelling-index",
                     cl::desc("Generate a clang attribute spelling index"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrSpellingListIndex); }));
} // end anonymous namespace
