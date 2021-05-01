set(LLVM_LINK_COMPONENTS
  )

set(xxx
  BinaryFormat
  Object
  ObjectYAML
  LLVMTestingSupport
  )

add_llvm_unittest(ObjectTests
  ArchiveTest.cpp
  ELFObjectFileTest.cpp
  ELFTypesTest.cpp
  ELFTest.cpp
  MinidumpTest.cpp
  ObjectFileTest.cpp
  SymbolSizeTest.cpp
  SymbolicFileTest.cpp
  XCOFFObjectFileTest.cpp
  )
