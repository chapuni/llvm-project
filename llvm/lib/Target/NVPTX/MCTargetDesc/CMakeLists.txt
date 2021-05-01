add_llvm_component_library(LLVMNVPTXDesc
  NVPTXInstPrinter.cpp
  NVPTXMCAsmInfo.cpp
  NVPTXMCTargetDesc.cpp
  NVPTXTargetStreamer.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  NVPTX
  )

set(xxx
  MC
  NVPTXInfo
  Support
  )
