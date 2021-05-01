set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Support
  Symbolize
  )

add_llvm_tool(sanstats
  sanstats.cpp

  DEPENDS
  intrinsics_gen
  )
