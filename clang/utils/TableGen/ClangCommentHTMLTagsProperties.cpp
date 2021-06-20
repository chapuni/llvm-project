#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-comment-html-tags-properties",
                     cl::desc("Generate efficient matchers for HTML tag "
                              "properties"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangCommentHTMLTagsProperties); }));
} // end anonymous namespace
