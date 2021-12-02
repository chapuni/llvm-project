set(LLVM_LINK_COMPONENTS
  BinaryFormat
  BitReader
  Object
  Option
  Support
  )

set(LLVM_TARGET_DEFINITIONS Options.td)
tablegen(LLVM Options.inc -gen-opt-parser-defs)

add_llvm_component_library(LLVMLibDriver
  LibDriver.cpp
  Options.inc

  LINK_COMPONENTS
  BinaryFormat
  BitReader
  Object
  Option
  Support
  )
