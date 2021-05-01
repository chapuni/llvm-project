set(LLVM_LINK_COMPONENTS
  )

set(xxx
  BinaryFormat
  )

add_llvm_unittest(BinaryFormatTests
  DwarfTest.cpp
  MachOTest.cpp
  MsgPackDocumentTest.cpp
  MsgPackReaderTest.cpp
  MsgPackWriterTest.cpp
  TestFileMagic.cpp
  )

