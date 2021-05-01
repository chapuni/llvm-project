set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Analysis
  AsmParser
  Core
  IPO
  Support
  TransformUtils
  )

add_llvm_unittest(IPOTests
  LowerTypeTests.cpp
  WholeProgramDevirt.cpp
  AttributorTest.cpp
  )
