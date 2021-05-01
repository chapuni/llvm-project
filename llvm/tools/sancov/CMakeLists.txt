set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AllTargetsDescs
  AllTargetsDisassemblers
  AllTargetsInfos
  DebugInfoDWARF
  DebugInfoPDB
  MC
  MCDisassembler
  Object
  Support
  Symbolize
  )

add_llvm_tool(sancov
  sancov.cpp
  )
