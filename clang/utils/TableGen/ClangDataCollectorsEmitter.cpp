#include "TableGenBackends.h"
#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/TableGenBackend.h"

using namespace llvm;

void clang::EmitClangDataCollectors(RecordKeeper &RK, raw_ostream &OS) {
  const auto &Defs = RK.getClasses();
  for (const auto &Entry : Defs) {
    Record &R = *Entry.second;
    OS << "DEF_ADD_DATA(" << R.getName() << ", {\n";
    auto Code = R.getValue("Code")->getValue();
    OS << Code->getAsUnquotedString() << "}\n)";
    OS << "\n";
  }
  OS << "#undef DEF_ADD_DATA\n";
}

namespace {
cl::opt<bool> Action("gen-clang-data-collectors",
                     cl::desc("Generate data collectors for AST nodes"),
                     cl::callback([](const bool &) { TableGen::RegisterAction(clang::EmitClangDataCollectors); }));
} // end anonymous namespace
