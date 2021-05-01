add_llvm_component_library(LLVMNVPTXInfo
  NVPTXTargetInfo.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  NVPTX
  )

set(xxx
  Support
  )
