set(LLVM_LINK_COMPONENTS
  Core
  Support
  )

add_clang_library(clangDependencyScanning
  DependencyScanningFilesystem.cpp
  DependencyScanningService.cpp
  DependencyScanningWorker.cpp
  DependencyScanningTool.cpp
  ModuleDepCollector.cpp

  LINK_LIBS
  clangAST
  clangBasic
  clangDriver
  clangFrontend
  clangFrontendTool
  clangLex
  clangParse
  clangSerialization
  clangTooling
)
