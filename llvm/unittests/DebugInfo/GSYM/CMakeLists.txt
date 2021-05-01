set(LLVM_LINK_COMPONENTS
  )

set(xxx
  DebugInfoDWARF
  DebugInfoGSYM
  MC
  Support
  ObjectYAML
  LLVMTestingSupport
  )

add_llvm_unittest(DebugInfoGSYMTests
  GSYMTest.cpp
  )
