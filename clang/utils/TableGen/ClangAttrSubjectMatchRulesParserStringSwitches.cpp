#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<bool> Action("gen-clang-attr-subject-match-rules-parser-string-switches",
                     cl::desc("Generate all parser-related attribute subject match rule"
			      "string switches"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(EmitClangAttrSubjectMatchRulesParserStringSwitches); }));
} // end anonymous namespace
