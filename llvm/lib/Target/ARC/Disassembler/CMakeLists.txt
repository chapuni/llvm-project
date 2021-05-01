add_llvm_component_library(LLVMARCDisassembler
  ARCDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  ARC
  )

set(xxx
  MCDisassembler
  Support
  ARCInfo
  )
