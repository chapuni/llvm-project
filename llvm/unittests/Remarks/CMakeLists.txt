set(LLVM_LINK_COMPONENTS
  )

set(xxx
  BitReader
  Remarks
  Support
  )

add_llvm_unittest(RemarksTests
  BitstreamRemarksFormatTest.cpp
  BitstreamRemarksParsingTest.cpp
  BitstreamRemarksSerializerTest.cpp
  RemarksAPITest.cpp
  RemarksLinkingTest.cpp
  RemarksStrTabParsingTest.cpp
  YAMLRemarksParsingTest.cpp
  YAMLRemarksSerializerTest.cpp
  )
