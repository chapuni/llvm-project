add_llvm_component_library(LLVMX86Disassembler
  X86Disassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  X86
  )

set(xxx
  MCDisassembler
  Support
  X86Info
  )
