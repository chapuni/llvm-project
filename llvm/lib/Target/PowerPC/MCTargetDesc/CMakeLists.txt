add_llvm_component_library(LLVMPowerPCDesc
  PPCAsmBackend.cpp
  PPCInstPrinter.cpp
  PPCMCTargetDesc.cpp
  PPCMCAsmInfo.cpp
  PPCMCCodeEmitter.cpp
  PPCMCExpr.cpp
  PPCPredicates.cpp
  PPCELFObjectWriter.cpp
  PPCXCOFFObjectWriter.cpp
  PPCELFStreamer.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  PowerPC
  )

set(xxx
  MC
  PowerPCInfo
  Support
  BinaryFormat
  )
