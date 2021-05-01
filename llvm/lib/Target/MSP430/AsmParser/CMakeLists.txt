add_llvm_component_library(LLVMMSP430AsmParser
  MSP430AsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  MSP430
)

set(xxx
  MC
  MCParser
  MSP430Desc
  MSP430Info
  Support
  )
