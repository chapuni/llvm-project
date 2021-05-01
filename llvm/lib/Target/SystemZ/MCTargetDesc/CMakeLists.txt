add_llvm_component_library(LLVMSystemZDesc
  SystemZInstPrinter.cpp
  SystemZMCAsmBackend.cpp
  SystemZMCAsmInfo.cpp
  SystemZMCCodeEmitter.cpp
  SystemZMCObjectWriter.cpp
  SystemZMCTargetDesc.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  SystemZ
  )

set(xxx
  MC
  Support
  SystemZInfo
  )
