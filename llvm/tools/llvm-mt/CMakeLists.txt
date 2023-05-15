set(LLVM_LINK_COMPONENTS
  Option
  Support
  WindowsManifest
  )

set(LLVM_TARGET_DEFINITIONS Opts.td)
tablegen(LLVM Opts.inc -gen-opt-parser-defs)

add_llvm_tool(llvm-mt
  llvm-mt.cpp

  Opts.inc

  GENERATE_DRIVER
  )
