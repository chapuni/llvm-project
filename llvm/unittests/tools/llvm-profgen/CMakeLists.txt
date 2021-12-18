set(LLVM_LINK_COMPONENTS
  Core
  Support
  )

add_llvm_unittest(LLVMProfgenTests
    ContextCompressionTest.cpp
  )

target_link_libraries(LLVMProfgenTests PRIVATE LLVMTestingSupport)
