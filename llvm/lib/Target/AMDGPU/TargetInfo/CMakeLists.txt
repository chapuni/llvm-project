add_llvm_component_library(LLVMAMDGPUInfo
  AMDGPUTargetInfo.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  AMDGPU
  )

#  Support
