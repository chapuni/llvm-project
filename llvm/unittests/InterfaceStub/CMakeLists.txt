set(LLVM_LINK_COMPONENTS
  )

set(xxx
  InterfaceStub
  LLVMTestingSupport
)

add_llvm_unittest(InterfaceStubTests
  ELFYAMLTest.cpp
)
