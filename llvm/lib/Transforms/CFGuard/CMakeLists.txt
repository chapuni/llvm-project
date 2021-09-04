add_llvm_component_library(LLVMCFGuard
  CFGuard.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms

  LINK_COMPONENTS
  Core
  Support
  )
