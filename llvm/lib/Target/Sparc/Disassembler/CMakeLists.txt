add_llvm_component_library(LLVMSparcDisassembler
  SparcDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  Sparc
  )

set(xxx
  MCDisassembler
  SparcInfo
  Support
  )
