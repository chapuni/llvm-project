add_llvm_component_library(LLVMXCoreDisassembler
  XCoreDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  XCore
  )

set(xxx
  MCDisassembler
  Support
  XCoreInfo
  )
