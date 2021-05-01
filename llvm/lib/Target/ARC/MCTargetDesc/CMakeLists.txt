add_llvm_component_library(LLVMARCDesc
  ARCInstPrinter.cpp
  ARCMCTargetDesc.cpp
  ARCMCAsmInfo.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  ARC
  )

set(xxx
  MC
  Support
  ARCInfo
  )
