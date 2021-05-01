add_llvm_component_library(LLVMBitWriter
  BitWriter.cpp
  BitcodeWriter.cpp
  BitcodeWriterPass.cpp
  ValueEnumerator.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  )

set(xxx
  Analysis
  Core
  MC
  Object
  Support
  )
