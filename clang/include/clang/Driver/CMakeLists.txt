set(LLVM_TARGET_DEFINITIONS Options.td)
tablegen(LLVM Options.inc -gen-opt-parser-defs)
add_public_tablegen_target(ClangDriverOptions)
set_property(GLOBAL APPEND PROPERTY CLANG_TABLEGEN_TARGETS ClangDriverOptions)
