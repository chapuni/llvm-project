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

add_llvm_example(OrcV2CBindingsReflectProcessSymbols
  OrcV2CBindingsReflectProcessSymbols.c
  )

export_executable_symbols(OrcV2CBindingsReflectProcessSymbols)
