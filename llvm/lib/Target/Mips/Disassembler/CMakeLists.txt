add_llvm_component_library(LLVMMipsDisassembler
  MipsDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  Mips
  )

set(xxx
  MCDisassembler
  MipsInfo
  Support
  )
