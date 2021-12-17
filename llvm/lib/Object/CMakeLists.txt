add_llvm_component_library(LLVMObject
  Archive.cpp
  ArchiveWriter.cpp
  Binary.cpp
  COFFImportFile.cpp
  COFFModuleDefinition.cpp
  COFFObjectFile.cpp
  Decompressor.cpp
  ELF.cpp
  ELFObjectFile.cpp
  Error.cpp
  FaultMapParser.cpp
  IRObjectFile.cpp
  IRSymtab.cpp
  MachOObjectFile.cpp
  MachOUniversal.cpp
  Minidump.cpp
  ModuleSymbolTable.cpp
  Object.cpp
  ObjectFile.cpp
  RecordStreamer.cpp
  RelocationResolver.cpp
  SymbolicFile.cpp
  SymbolSize.cpp
  TapiFile.cpp
  TapiUniversal.cpp
  MachOUniversalWriter.cpp
  WasmObjectFile.cpp
  WindowsMachineFlag.cpp
  WindowsResource.cpp
  XCOFFObjectFile.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Object

  # LINK_LIBS
  # PRIVATE
  # llvm_vcsrevision_h

  LINK_COMPONENTS
  BitReader
  Core
  MC
  BinaryFormat
  MCParser
  Support
  TextAPI
  )

add_dependencies(LLVMObject llvm_vcsrevision_h)
