set(LLVM_TARGET_DEFINITIONS Options.td)
tablegen(LLVM Options.inc -gen-opt-parser-defs)

set(LLVM_LINK_COMPONENTS
  AllTargetsCodeGens
  AllTargetsDescs
  AllTargetsInfos
  DWARFLinker
  DebugInfoDWARF
  MC
  ObjCopy
  Object
  Option
  Support
  Target
  TargetParser
  )

add_llvm_tool(llvm-dwarfutil
  llvm-dwarfutil.cpp
  DebugInfoLinker.cpp

  Options.inc

  DEPENDS
  intrinsics_gen
  )
