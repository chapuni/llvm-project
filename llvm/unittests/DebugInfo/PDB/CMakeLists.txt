set(LLVM_LINK_COMPONENTS
  )

set(xxx
  DebugInfoCodeView
  DebugInfoMSF
  DebugInfoPDB
  LLVMTestingSupport
  )

add_llvm_unittest_with_input_files(DebugInfoPDBTests
  HashTableTest.cpp
  NativeSessionTest.cpp
  NativeSymbolReuseTest.cpp
  StringTableBuilderTest.cpp
  PDBApiTest.cpp
  )
