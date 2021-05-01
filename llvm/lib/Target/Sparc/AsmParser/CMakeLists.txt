add_llvm_component_library(LLVMSparcAsmParser
  SparcAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  Sparc
  )

set(xxx
  MC
  MCParser
  SparcDesc
  SparcInfo
  Support
  )
