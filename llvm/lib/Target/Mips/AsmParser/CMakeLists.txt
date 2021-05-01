add_llvm_component_library(LLVMMipsAsmParser
  MipsAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  Mips
  )

set(xxx
  MC
  MCParser
  MipsDesc
  MipsInfo
  Support
  )
