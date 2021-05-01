set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  IRReader
  OrcJIT
  OrcTargetProcess
  ExecutionEngine
  Support
  nativecodegen
  Analysis
  Passes
  )

add_llvm_example(SpeculativeJIT
  SpeculativeJIT.cpp
  )
