add_llvm_component_library(LLVMWebAssemblyDisassembler
  WebAssemblyDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  WebAssembly
  )

set(xxx
  WebAssemblyDesc
  MCDisassembler
  WebAssemblyInfo
  Support
  MC
  )
