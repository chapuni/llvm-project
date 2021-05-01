add_llvm_component_library(LLVMLanaiDesc
  LanaiAsmBackend.cpp
  LanaiELFObjectWriter.cpp
  LanaiInstPrinter.cpp
  LanaiMCAsmInfo.cpp
  LanaiMCCodeEmitter.cpp
  LanaiMCExpr.cpp
  LanaiMCTargetDesc.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  Lanai
)

set(xxx
  LanaiInfo
  MC
  MCDisassembler
  Support
  )
