set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Demangle
  Support
  )

add_llvm_tool(llvm-undname
  llvm-undname.cpp
  )
