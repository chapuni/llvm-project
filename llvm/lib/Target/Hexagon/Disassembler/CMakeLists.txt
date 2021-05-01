add_llvm_component_library(LLVMHexagonDisassembler
  HexagonDisassembler.cpp

  LINK_COMPONENTS

  ADD_TO_COMPONENT
  Hexagon
  )

set(xxx
  HexagonDesc
  HexagonInfo
  MC
  MCDisassembler
  Support
  )
