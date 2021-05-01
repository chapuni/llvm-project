set(LLVM_LINK_COMPONENTS
  )

set(xxx
  ${LLVM_TARGETS_TO_BUILD}
  DebugInfoDWARF
  DebugInfoGSYM
  MC
  Object
  Support
  Target
  )

add_llvm_tool(llvm-gsymutil
  llvm-gsymutil.cpp

  )
