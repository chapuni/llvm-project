set(LLVM_GENERATED_INCLUDES_BASE ${CMAKE_CURRENT_BINARY_DIR}/../..)
set(LLVM_TARGET_DEFINITIONS Options.td)
tablegen(LLVM Options.inc -gen-opt-parser-defs)
add_public_tablegen_target(ClangDriverOptions EXPORT CLANG)
