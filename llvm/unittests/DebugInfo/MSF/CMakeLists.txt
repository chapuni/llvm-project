set(LLVM_LINK_COMPONENTS
  )

set(xxx
  DebugInfoMSF
  LLVMTestingSupport
  )

add_llvm_unittest(DebugInfoMSFTests
  MappedBlockStreamTest.cpp
  MSFBuilderTest.cpp
  MSFCommonTest.cpp
  )
