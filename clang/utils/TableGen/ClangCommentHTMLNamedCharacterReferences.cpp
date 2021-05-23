#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-comment-html-named-character-references",
                     cl::desc("Generate function to translate named character "
                              "references to UTF-8 sequences"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangCommentHTMLNamedCharacterReferences); }));
} // end anonymous namespace
