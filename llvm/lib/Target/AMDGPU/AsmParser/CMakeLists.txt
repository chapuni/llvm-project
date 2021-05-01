add_llvm_component_library(LLVMAMDGPUAsmParser
  AMDGPUAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  AMDGPU
  )

set(xxx
  MC
  MCParser
  AMDGPUDesc
  AMDGPUInfo
  AMDGPUUtils
  Support
  )

add_dependencies(LLVMAMDGPUAsmParser LLVMAMDGPUUtils)
