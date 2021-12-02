set(LLVM_LINK_COMPONENTS
  X86
  Exegesis
  Core
  Support
  CodeGen
  )

add_llvm_library(LLVMExegesisX86
  DISABLE_LLVM_LINK_LLVM_DYLIB
  STATIC
  Target.cpp
  X86Counter.cpp
  )
