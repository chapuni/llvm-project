#include "TableGenBackends.h" // Declares all backends.
#include "llvm/Support/CommandLine.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {

TableGen::Action Action(EmitDirectivesImpl, "gen-directive-impl",
                        "Generate directive related implementation code");

}
