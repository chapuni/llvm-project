set(LLVM_LINK_COMPONENTS
  )

set(xxx
  ${LLVM_TARGETS_TO_BUILD}
  JITLink
  Object
  OrcShared
  OrcTargetProcess
  RuntimeDyld
  Support
  LLVMTestingSupport
  )

add_llvm_unittest(JITLinkTests
    LinkGraphTests.cpp
  )
