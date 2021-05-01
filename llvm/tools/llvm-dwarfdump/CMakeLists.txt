set(LLVM_LINK_COMPONENTS
  )

set(xxx
  DebugInfoDWARF
  AllTargetsDescs
  AllTargetsInfos
  MC
  Object
  Support
  )

add_llvm_tool(llvm-dwarfdump
  SectionSizes.cpp
  Statistics.cpp
  llvm-dwarfdump.cpp
  )

add_subdirectory(fuzzer)
