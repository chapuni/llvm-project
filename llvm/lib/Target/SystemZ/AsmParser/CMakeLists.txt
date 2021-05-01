add_llvm_component_library(LLVMSystemZAsmParser
  SystemZAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  SystemZ
  )

set(xxx
  MC
  MCParser
  Support
  SystemZDesc
  SystemZInfo
  )
