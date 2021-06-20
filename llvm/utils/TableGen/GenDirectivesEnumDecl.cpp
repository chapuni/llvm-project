#include "TableGenBackends.h" // Declares all backends.
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {

TableGen::Action
    Action(EmitDirectivesDecl, "gen-directive-decl",
           "Generate directive related declaration code (header file)");

}
