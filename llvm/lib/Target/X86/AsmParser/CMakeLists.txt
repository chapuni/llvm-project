add_llvm_component_library(LLVMX86AsmParser
  X86AsmParser.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  X86
  )

set(xxx
  MC
  MCParser
  Support
  X86Desc
  X86Info
  )
