set(LLVM_LINK_COMPONENTS
  )

set(xxx
  FileCheck
  Support
  LLVMTestingSupport
)

add_llvm_unittest(FileCheckTests
  FileCheckTest.cpp
)
