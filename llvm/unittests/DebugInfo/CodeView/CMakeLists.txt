set(LLVM_LINK_COMPONENTS
  )

set(xxx
  DebugInfoCodeView
  LLVMTestingSupport
  )

add_llvm_unittest(DebugInfoCodeViewTests
  RandomAccessVisitorTest.cpp
  TypeHashingTest.cpp
  TypeIndexDiscoveryTest.cpp
  )
