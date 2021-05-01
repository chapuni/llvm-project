set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AllTargetsDisassemblers
  AllTargetsDescs
  AllTargetsInfos
  DebugInfoDWARF
  ExecutionEngine
  MC
  Object
  RuntimeDyld
  Support
  )

add_llvm_tool(llvm-rtdyld
  llvm-rtdyld.cpp
  )
