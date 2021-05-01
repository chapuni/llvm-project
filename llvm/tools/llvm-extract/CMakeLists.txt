set(LLVM_LINK_COMPONENTS
  )

set(xxx
  BitWriter
  Core
  IPO
  IRReader
  Support
  )

add_llvm_tool(llvm-extract
  llvm-extract.cpp

  DEPENDS
  intrinsics_gen
  )
