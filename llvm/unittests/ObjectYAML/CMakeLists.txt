set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Object
  ObjectYAML
  LLVMTestingSupport
  )

add_llvm_unittest(ObjectYAMLTests
  DWARFYAMLTest.cpp
  ELFYAMLTest.cpp
  MinidumpYAMLTest.cpp
  YAML2ObjTest.cpp
  YAMLTest.cpp
  )
