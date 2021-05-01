set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  ExecutionEngine
  IRReader
  OrcJIT
  Support
  nativecodegen
  )

add_llvm_example(LLJITWithLazyReexports
  LLJITWithLazyReexports.cpp
  )
