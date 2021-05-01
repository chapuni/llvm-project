add_llvm_component_library(LLVMSystemZDisassembler
  SystemZDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  SystemZ
  )

set(xxx
  MC
  MCDisassembler
  Support
  SystemZDesc
  SystemZInfo
  )
