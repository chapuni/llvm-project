add_llvm_component_library(LLVMAVRDisassembler
  AVRDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  AVR
)

set(xxx
  MCDisassembler
  AVRInfo
  Support
  )
