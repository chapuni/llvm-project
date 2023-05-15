set(LLVM_TARGET_DEFINITIONS Options.td)
tablegen(LLVM Options.inc -gen-opt-parser-defs)

add_llvm_component_library(LLVMDlltoolDriver
  DlltoolDriver.cpp

  Options.inc

  LINK_COMPONENTS
  Object
  Option
  Support
  TargetParser
  )
