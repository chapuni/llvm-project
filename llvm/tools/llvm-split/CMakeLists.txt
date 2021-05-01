set(LLVM_LINK_COMPONENTS
  )

set(xxx
  TransformUtils
  BitWriter
  Core
  IRReader
  Support
  )

add_llvm_tool(llvm-split
  llvm-split.cpp

  DEPENDS
  intrinsics_gen
  )
