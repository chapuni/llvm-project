add_llvm_component_library(LLVMX86Info
  X86TargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  LINK_LIBS
  PRIVATE
  X86CommonTableGen

  ADD_TO_COMPONENT
  X86
  )
