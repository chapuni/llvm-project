include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_component_library(LLVMAMDGPUDisassembler
  AMDGPUDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  AMDGPU
  )

set(xxx
  AMDGPUDesc
  AMDGPUInfo
  AMDGPUUtils
  MC
  MCDisassembler
  Support
  )

add_dependencies(LLVMAMDGPUDisassembler AMDGPUCommonTableGen LLVMAMDGPUUtils)
