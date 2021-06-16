#include "TableGenBackends.h"
#include "llvm/Support/CommandLine.h"
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

cl::opt<bool> Action("gen-clang-diags-defs",
                     cl::desc("Generate Clang diagnostics definitions"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(Emit); }));
} // end anonymous namespace
