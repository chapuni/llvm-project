#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-subject-match-rule-list",
                     cl::desc("Generate a clang attribute subject match rule list"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrSubjectMatchRuleList); }));
} // end anonymous namespace
