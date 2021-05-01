set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Analysis
  Core
  FrontendOpenMP
  FrontendOpenACC
  Support
  Passes
  TransformUtils
  LLVMTestingSupport
  )

add_llvm_unittest(LLVMFrontendTests
  OpenACCTest.cpp
  OpenMPContextTest.cpp
  OpenMPIRBuilderTest.cpp
  OpenMPParsingTest.cpp

  DEPENDS
  acc_gen
  omp_gen
  )
