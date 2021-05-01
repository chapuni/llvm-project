set(LLVM_LINK_COMPONENTS
  )

set(xxx
  IRReader
  BitReader
  BitWriter
  Core
  Support
  )

add_llvm_tool(llvm-modextract
  llvm-modextract.cpp
  )
