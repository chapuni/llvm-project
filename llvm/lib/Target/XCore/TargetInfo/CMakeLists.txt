add_llvm_component_library(LLVMXCoreInfo
  XCoreTargetInfo.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  XCore
  )

set(xxx
  Support
  )
