add_llvm_component_library(LLVMAVRAsmParser
  AVRAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  AVR
)

set(xxx
  MC
  MCParser
  AVRDesc
  AVRInfo
  Support
  )
