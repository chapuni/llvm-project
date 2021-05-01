add_llvm_component_library(LLVMVEDisassembler
  VEDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  VE
  )

set(xxx
  MCDisassembler
  VEInfo
  Support
  )
