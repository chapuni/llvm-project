set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  ProfileData
  Support
  )

add_llvm_tool(llvm-profdata
  llvm-profdata.cpp

  DEPENDS
  intrinsics_gen
  )
