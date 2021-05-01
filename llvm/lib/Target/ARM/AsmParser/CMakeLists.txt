add_llvm_component_library(LLVMARMAsmParser
  ARMAsmParser.cpp

  LINK_COMPONENTS
  ARMDesc
  ARMInfo
  ARMUtils
  MC
  MCParser
  Support

  ADD_TO_COMPONENT
  ARM
  )
