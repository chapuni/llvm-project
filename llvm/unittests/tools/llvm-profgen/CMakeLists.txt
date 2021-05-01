set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Support
  LLVMTestingSupport
  )

add_llvm_unittest(LLVMProfgenTests
    ContextCompressionTest.cpp
  )

add_dependencies(LLVMProfgenTests intrinsics_gen)
