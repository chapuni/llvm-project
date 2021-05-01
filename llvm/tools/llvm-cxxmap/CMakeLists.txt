set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  Support
  )

add_llvm_tool(llvm-cxxmap
  llvm-cxxmap.cpp
  )
