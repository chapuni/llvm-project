set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AllTargetsAsmParsers
  AllTargetsDescs
  AllTargetsDisassemblers
  AllTargetsInfos
  MC
  MCParser
  Object
  Support
  Symbolize
  LLVMCFIVerify
  )

add_llvm_unittest(CFIVerifyTests
  FileAnalysis.cpp
  GraphBuilder.cpp
  )
