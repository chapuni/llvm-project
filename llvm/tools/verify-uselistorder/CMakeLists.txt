set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AsmParser
  BitReader
  BitWriter
  Core
  IRReader
  Support
  )

add_llvm_tool(verify-uselistorder
  verify-uselistorder.cpp

  DEPENDS
  intrinsics_gen
  )
