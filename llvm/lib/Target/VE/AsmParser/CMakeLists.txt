add_llvm_component_library(LLVMVEAsmParser
  VEAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  VE
  )

set(xxx
  MC
  MCParser
  VEDesc
  VEInfo
  Support
  )
