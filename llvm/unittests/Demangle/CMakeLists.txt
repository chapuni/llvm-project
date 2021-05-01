set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Demangle
  Support
)

add_llvm_unittest(DemangleTests
  DemangleTest.cpp
  ItaniumDemangleTest.cpp
  PartialDemangleTest.cpp
)
