set(LLVM_LINK_COMPONENTS
  )

set(xxx
  LineEditor
  Support
  )

add_llvm_unittest(LineEditorTests
  LineEditor.cpp
  )
