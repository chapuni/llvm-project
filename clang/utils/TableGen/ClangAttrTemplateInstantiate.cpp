#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitClangAttrTemplateInstantiate,
                        "gen-clang-attr-template-instantiate",
                        "Generate a clang template instantiate code");
}
