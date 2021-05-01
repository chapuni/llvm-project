set(LLVM_LINK_COMPONENTS
  )

set(xxx
  BitReader
  Core
  ExecutionEngine
  OrcJIT
  OrcTargetProcess
  Support
  nativecodegen
  )

add_llvm_example(LLJITWithThinLTOSummaries
  LLJITWithThinLTOSummaries.cpp
  )
