add_llvm_component_library(LLVMXCoreDesc
  XCoreInstPrinter.cpp
  XCoreMCTargetDesc.cpp
  XCoreMCAsmInfo.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  XCore
  )

set(xxx
  MC
  Support
  XCoreInfo
  )
