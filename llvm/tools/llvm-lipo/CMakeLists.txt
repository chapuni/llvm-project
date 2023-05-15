set(LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  Object
  Option
  Support
  TargetParser
  TextAPI
  Core
  BinaryFormat
)

set(LLVM_TARGET_DEFINITIONS LipoOpts.td)
tablegen(LLVM LipoOpts.inc -gen-opt-parser-defs)

add_llvm_tool(llvm-lipo
  llvm-lipo.cpp

  LipoOpts.inc

  GENERATE_DRIVER
  )

if(LLVM_INSTALL_CCTOOLS_SYMLINKS)
  add_llvm_tool_symlink(lipo llvm-lipo)
endif()
