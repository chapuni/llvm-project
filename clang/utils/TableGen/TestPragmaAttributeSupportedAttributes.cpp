#include "TableGenBackends.h"
#include "llvm/TableGen/Main.h"

using namespace llvm;

namespace {
TableGen::Action Action(clang::EmitTestPragmaAttributeSupportedAttributes,
                        "gen-clang-test-pragma-attribute-supported-attributes",
                        "Generate a list of attributes supported by #pragma "
                        "clang attribute for testing purposes");
}
