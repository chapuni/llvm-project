set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  ExecutionEngine
  Interpreter
  MC
  MCJIT
  Support
  nativecodegen
  )

add_llvm_example(HowToUseJIT
  HowToUseJIT.cpp
  )
