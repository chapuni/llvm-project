set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Analysis
  Core
  Support
  )

add_llvm_tool(llvm-stress
  llvm-stress.cpp

  DEPENDS
  intrinsics_gen
  )
