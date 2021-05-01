add_llvm_component_library(LLVMSystemZInfo
  SystemZTargetInfo.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  SystemZ
  )

set(xxx
  Support
  )
