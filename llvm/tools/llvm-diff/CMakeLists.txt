set(LLVM_LINK_COMPONENTS
  Core
  IRReader
  Support
  )

add_llvm_tool(llvm-diff
  llvm-diff.cpp
  )

add_subdirectory(lib)
target_link_libraries(llvm-diff PRIVATE LLVMDiff)
