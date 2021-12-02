add_llvm_component_library(LLVMMCJIT
  MCJIT.cpp

  LINK_COMPONENTS
  Core
  ExecutionEngine
  Object
  RuntimeDyld
  Support
  Target
  )
