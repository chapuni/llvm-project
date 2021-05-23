#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-comment-command-info",
                     cl::desc("Generate command properties for commands that "
                              "are used in documentation comments"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangCommentCommandInfo); }));
} // end anonymous namespace
