set(LLVM_LINK_COMPONENTS
  )

set(xxx
  OrcShared
  OrcJIT
  RuntimeDyld
  Support
  )

add_llvm_utility(lli-child-target
  ChildTarget.cpp

  DEPENDS
  intrinsics_gen
)

