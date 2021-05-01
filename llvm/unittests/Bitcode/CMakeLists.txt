set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AsmParser
  BitReader
  BitWriter
  Core
  Support
  )

add_llvm_unittest(BitcodeTests
  BitReaderTest.cpp
  DataLayoutUpgradeTest.cpp
  )
