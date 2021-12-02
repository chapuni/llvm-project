add_llvm_component_library(LLVMFrontendOpenMP
  OMP.cpp
  OMPContext.cpp
  OMPIRBuilder.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Frontend
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Frontend/OpenMP

  LINK_LIBS
  PUBLIC
  omp_gen

  PRIVATE

  LINK_COMPONENTS
  Core
  Support
  TransformUtils
  Analysis
  MC
  Scalar
  )
