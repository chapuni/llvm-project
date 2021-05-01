set(LLVM_LINK_COMPONENTS
  )

set(xxx
  Core
  IRReader
  JITLink
  OrcJIT
  Support
  nativecodegen
  )

add_llvm_example(LLJITWithObjectLinkingLayerPlugin
  LLJITWithObjectLinkingLayerPlugin.cpp
  )
