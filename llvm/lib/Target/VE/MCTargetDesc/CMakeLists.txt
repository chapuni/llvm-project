add_llvm_component_library(LLVMVEDesc
  VEAsmBackend.cpp
  VEELFObjectWriter.cpp
  VEInstPrinter.cpp
  VEMCAsmInfo.cpp
  VEMCCodeEmitter.cpp
  VEMCExpr.cpp
  VEMCTargetDesc.cpp
  VETargetStreamer.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  VE
  )

set(xxx
  MC
  VEInfo
  Support
  )
