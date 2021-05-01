set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Analysis
  AsmParser
  Core
  Support
)
add_llvm_fuzzer(vfabi-demangler-fuzzer
  vfabi-demangler-fuzzer.cpp
)
