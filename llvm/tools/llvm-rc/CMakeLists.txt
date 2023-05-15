set(LLVM_LINK_COMPONENTS
  Object
  Option
  Support
  TargetParser
  )

set(LLVM_TARGET_DEFINITIONS Opts.td)
tablegen(LLVM Opts.inc -gen-opt-parser-defs)

set(LLVM_TARGET_DEFINITIONS WindresOpts.td)
tablegen(LLVM WindresOpts.inc -gen-opt-parser-defs)

add_llvm_tool(llvm-rc
  llvm-rc.cpp
  ResourceFileWriter.cpp
  ResourceScriptCppFilter.cpp
  ResourceScriptParser.cpp
  ResourceScriptStmt.cpp
  ResourceScriptToken.cpp

  Opts.inc
  WindresOpts.inc

  GENERATE_DRIVER
  )

add_llvm_tool_symlink(llvm-windres llvm-rc)

if(LLVM_INSTALL_BINUTILS_SYMLINKS)
  add_llvm_tool_symlink(windres llvm-rc)
endif()
