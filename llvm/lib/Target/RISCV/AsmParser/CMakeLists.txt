add_llvm_component_library(LLVMRISCVAsmParser
  RISCVAsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  RISCV
  )

set(xxx
  MC
  MCParser
  RISCVDesc
  RISCVInfo
  Support
  )
