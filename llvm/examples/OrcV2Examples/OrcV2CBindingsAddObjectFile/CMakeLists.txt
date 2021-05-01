set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  ExecutionEngine
  IRReader
  JITLink
  MC
  OrcJIT
  Support
  Target
  nativecodegen
  )

add_llvm_example(OrcV2CBindingsAddObjectFile
  OrcV2CBindingsAddObjectFile.c
  )
