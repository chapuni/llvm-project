set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  ExecutionEngine
  IRReader
  JITLink
  OrcJIT
  Support
  nativecodegen
  )

add_llvm_example(LLJITWithInitializers
  LLJITWithInitializers.cpp
  )
