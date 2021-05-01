set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  Coverage
  ProfileData
  Support
  LLVMTestingSupport
  )

add_llvm_unittest(ProfileDataTests
  CoverageMappingTest.cpp
  InstrProfDataTest.cpp
  InstrProfTest.cpp
  SampleProfTest.cpp
  )
