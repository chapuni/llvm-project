set(LLVM_LINK_COMPONENTS
  Option
  Support
  )

set(LLVM_TARGET_DEFINITIONS Opts.td)
tablegen(LLVM Opts.inc -gen-opt-parser-defs)

add_llvm_unittest(OptionTests
  OptionParsingTest.cpp
  OptionMarshallingTest.cpp

  Opts.inc
  )
