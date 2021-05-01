add_llvm_component_library(LLVMWebAssemblyAsmParser
  WebAssemblyAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  WebAssembly
  )

set(xxx
  MC
  MCParser
  WebAssemblyInfo
  Support
  )
