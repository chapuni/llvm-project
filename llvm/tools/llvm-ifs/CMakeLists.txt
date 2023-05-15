set(LLVM_LINK_COMPONENTS
  BinaryFormat
  InterfaceStub
  ObjectYAML
  Option
  Support
  TargetParser
  TextAPI
  )

set(LLVM_TARGET_DEFINITIONS Opts.td)
tablegen(LLVM Opts.inc -gen-opt-parser-defs)

add_llvm_tool(llvm-ifs
  ErrorCollector.cpp
  llvm-ifs.cpp

  Opts.inc

  GENERATE_DRIVER
  )
