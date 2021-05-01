set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  ExecutionEngine
  IPO
  IRReader
  OrcJIT
  ScalarOpts
  Support
  nativecodegen
  )

add_llvm_example(LLJITWithOptimizingIRTransform
  LLJITWithOptimizingIRTransform.cpp
  )
