add_llvm_component_library(LLVMLanaiDisassembler
  LanaiDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  Lanai
  )

set(xxx
  LanaiDesc
  LanaiInfo
  MC
  MCDisassembler
  Support
  )
