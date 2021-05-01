add_llvm_component_library(LLVMBPFDisassembler
  BPFDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  BPF
)

set(xxx
  MCDisassembler
  BPFInfo
  Support
  )

