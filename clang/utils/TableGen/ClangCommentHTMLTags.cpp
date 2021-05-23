#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-comment-html-tags",
                     cl::desc("Generate efficient matchers for HTML tag "
                              "names that are used in documentation comments"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangCommentHTMLTags); }));
} // end anonymous namespace
