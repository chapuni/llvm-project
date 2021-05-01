set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AllTargetsInfos
  Object
  Support
  )

add_llvm_tool(llvm-cxxdump
  llvm-cxxdump.cpp
  Error.cpp
  )
