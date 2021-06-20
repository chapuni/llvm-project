#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(
    clang::EmitClangAttrSubjectMatchRulesParserStringSwitches,
    "gen-clang-attr-subject-match-rules-parser-string-switches",
    "Generate all parser-related attribute subject match rulestring switches");
}
