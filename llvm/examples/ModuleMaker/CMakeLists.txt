set(LLVM_LINK_COMPONENTS
  )

set(xxx
  BitWriter
  Core
  Support
  )

add_llvm_example(ModuleMaker
  ModuleMaker.cpp
  )
