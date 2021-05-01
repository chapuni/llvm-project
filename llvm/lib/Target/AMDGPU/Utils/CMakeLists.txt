add_llvm_component_library(LLVMAMDGPUUtils
  AMDGPUBaseInfo.cpp
  AMDKernelCodeTUtils.cpp
  AMDGPUAsmUtils.cpp
  AMDGPUPALMetadata.cpp

  LINK_COMPONENTS
  BinaryFormat
  Core
  MC
  Support

  ADD_TO_COMPONENT
  AMDGPU
  )
