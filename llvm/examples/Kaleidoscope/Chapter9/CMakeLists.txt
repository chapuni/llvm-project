set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  ExecutionEngine
  Object
  OrcJIT
  Support
  native
  )

add_kaleidoscope_chapter(Kaleidoscope-Ch9
  toy.cpp
  )

export_executable_symbols(Kaleidoscope-Ch9)
