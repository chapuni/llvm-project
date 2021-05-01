set(LLVM_LINK_COMPONENTS
  )

set(xxx
  BitWriter
  Core
  ExecutionEngine
  MC
  MCJIT
  Support
  nativecodegen
  )

add_llvm_example(BrainF
  BrainF.cpp
  BrainFDriver.cpp
  )
