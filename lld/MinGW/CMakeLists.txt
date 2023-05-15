set(LLVM_TARGET_DEFINITIONS Options.td)
tablegen(LLVM Options.inc -gen-opt-parser-defs)

add_lld_library(lldMinGW
  Driver.cpp

  Options.inc

  LINK_COMPONENTS
  Option
  Support
  TargetParser

  LINK_LIBS
  lldCOFF
  lldCommon

  DEPENDS
  intrinsics_gen
  )
