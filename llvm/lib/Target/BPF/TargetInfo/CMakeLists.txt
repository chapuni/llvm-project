add_llvm_component_library(LLVMBPFInfo
  BPFTargetInfo.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  BPF
  )

#  Support
