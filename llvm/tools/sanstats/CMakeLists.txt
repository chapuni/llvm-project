set(LLVM_LINK_COMPONENTS
  Support
  Symbolize
  TransformUtils
  )

add_llvm_tool(sanstats
  sanstats.cpp
  )
