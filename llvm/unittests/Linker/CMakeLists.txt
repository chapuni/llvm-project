set(LLVM_LINK_COMPONENTS
  )

set(xxx
  AsmParser
  core
  linker
  )

add_llvm_unittest(LinkerTests
  LinkModulesTest.cpp
  )
