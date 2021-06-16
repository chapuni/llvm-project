set(LLVM_LINK_COMPONENTS
  Support
  )

add_clang_tool(clang-scan-deps
  ClangScanDeps.cpp
  )

set(CLANG_SCAN_DEPS_LIB_DEPS
  clangBasic
  clangDependencyScanning
  clangTooling
  )

clang_target_link_libraries(clang-scan-deps
  PRIVATE
  ${CLANG_SCAN_DEPS_LIB_DEPS}
  )

