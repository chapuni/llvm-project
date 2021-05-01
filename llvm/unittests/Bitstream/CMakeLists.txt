set(LLVM_LINK_COMPONENTS
  )

set(xxx
  BitstreamReader
  )

add_llvm_unittest(BitstreamTests
  BitstreamReaderTest.cpp
  BitstreamWriterTest.cpp
  )
