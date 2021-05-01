add_llvm_component_library(LLVMARMDisassembler
  ARMDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  ARM
  )

set(xxx
  ARMDesc
  ARMInfo
  MCDisassembler
  Support
  ARMUtils
  )
