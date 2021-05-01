add_llvm_component_library(LLVMBPFAsmParser
  BPFAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  BPF
  )

set(xxx
  MC
  MCParser
  BPFDesc
  BPFInfo
  Support
  )
