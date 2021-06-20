#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action
    Action(clang::EmitClangAttrParserStringSwitches,
           "gen-clang-attr-parser-string-switches",
           "Generate all parser-related attribute string switches");
}
