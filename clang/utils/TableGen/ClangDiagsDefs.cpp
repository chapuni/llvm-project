#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;
using namespace clang;

namespace {
cl::opt<std::string>
    ClangComponent("clang-component",
                   cl::desc("Only use warnings from specified component"),
                   cl::value_desc("component"), cl::Hidden);

void Emit(RecordKeeper &Records, raw_ostream &OS) {
  EmitClangDiagsDefs(Records, OS, ClangComponent);
}

TableGen::Action Action(Emit, "gen-clang-diags-defs",
                        "Generate Clang diagnostics definitions");
} // namespace
