#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrSubjectMatchRuleList,
                        "gen-clang-attr-subject-match-rule-list",
                        "Generate a clang attribute subject match rule list");
}
