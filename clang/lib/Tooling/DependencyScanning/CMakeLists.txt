set(LLVM_LINK_COMPONENTS
  Support
  )

add_clang_library(clangDependencyScanning
  DependencyScanningFilesystem.cpp
  DependencyScanningService.cpp
  DependencyScanningWorker.cpp
  DependencyScanningTool.cpp
  ModuleDepCollector.cpp

  LINK_LIBS
  clangBasic
  clangFrontend
  clangLex
  clangSerialization
  clangTooling
)
