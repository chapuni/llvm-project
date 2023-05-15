add_llvm_component_library(LLVMFrontendOpenACC
  ACC.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Frontend
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Frontend/OpenACC

  LINK_COMPONENTS
  Support

  DEPENDS
  acc_gen
  )
