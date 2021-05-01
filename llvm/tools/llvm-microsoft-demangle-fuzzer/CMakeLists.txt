set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Demangle
  FuzzMutate
  Support
)

add_llvm_fuzzer(llvm-microsoft-demangle-fuzzer
  llvm-microsoft-demangle-fuzzer.cpp
  DUMMY_MAIN DummyDemanglerFuzzer.cpp
  )
