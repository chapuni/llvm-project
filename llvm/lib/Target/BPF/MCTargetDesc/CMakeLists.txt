add_llvm_component_library(LLVMBPFDesc
  BPFMCTargetDesc.cpp
  BPFAsmBackend.cpp
  BPFInstPrinter.cpp
  BPFMCCodeEmitter.cpp
  BPFELFObjectWriter.cpp

  LINK_COMPONENTS
  BPFInfo
  MC
  Support

  ADD_TO_COMPONENT
  BPF
  )
