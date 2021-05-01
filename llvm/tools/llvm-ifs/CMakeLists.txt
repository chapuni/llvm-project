set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Object
  Support
  TextAPI
  ObjectYAML
  )

add_llvm_tool(llvm-ifs
  llvm-ifs.cpp
  )
