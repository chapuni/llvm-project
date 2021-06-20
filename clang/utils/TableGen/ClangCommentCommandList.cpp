#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-comment-command-list",
                     cl::desc("Generate list of commands that are used in "
			      "documentation comments"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangCommentCommandList); }));
} // end anonymous namespace
