set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AsmParser
  Core
  Support
  )

add_llvm_unittest(AsmParserTests
  AsmParserTest.cpp
  )
