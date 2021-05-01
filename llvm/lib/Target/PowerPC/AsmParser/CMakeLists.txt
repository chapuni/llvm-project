add_llvm_component_library(LLVMPowerPCAsmParser
  PPCAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  PowerPC
  )

set(xxx
  MC
  MCParser
  PowerPCDesc
  PowerPCInfo
  Support
  )
