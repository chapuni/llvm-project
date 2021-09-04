add_llvm_component_library(LLVMBitWriter
  BitWriter.cpp
  BitcodeWriter.cpp
  BitcodeWriterPass.cpp
  ValueEnumerator.cpp

  LINK_COMPONENTS
  Analysis
  Core
  MC
  Object
  Support
  )
