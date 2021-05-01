add_llvm_component_library(LLVMRISCVDisassembler
  RISCVDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  RISCV
  )

set(xxx
  MCDisassembler
  RISCVInfo
  Support
  )
