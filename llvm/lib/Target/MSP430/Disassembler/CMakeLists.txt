add_llvm_component_library(LLVMMSP430Disassembler
  MSP430Disassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  MSP430
  )

set(xxx
  MCDisassembler
  MSP430Info
  Support
  )
