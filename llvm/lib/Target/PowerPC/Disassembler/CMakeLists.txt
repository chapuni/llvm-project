add_llvm_component_library(LLVMPowerPCDisassembler
  PPCDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  PowerPC
  )

set(xxx
  MCDisassembler
  PowerPCInfo
  Support
  )
