set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AsmParser
  BitWriter
  Core
  Support
  )

add_llvm_tool(llvm-as
  llvm-as.cpp

  DEPENDS
  intrinsics_gen
  )
