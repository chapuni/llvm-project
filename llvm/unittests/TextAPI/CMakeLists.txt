set(LLVM_LINK_COMPONENTS
  )

set(xxx
  TextAPI
  LLVMTestingSupport
)

add_llvm_unittest(TextAPITests
  TextStubV1Tests.cpp
  TextStubV2Tests.cpp
  TextStubV3Tests.cpp
  TextStubV4Tests.cpp
)
