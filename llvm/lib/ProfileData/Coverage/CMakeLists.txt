add_llvm_component_library(LLVMCoverage
  CoverageMapping.cpp
  CoverageMappingWriter.cpp
  CoverageMappingReader.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/ProfileData/Coverage

  LINK_COMPONENTS
  Core
  Object
  ProfileData
  Support
  )
