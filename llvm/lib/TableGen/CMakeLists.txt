add_llvm_component_library(LLVMTableGen
  DetailedRecordsBackend.cpp
  Error.cpp
  JSONBackend.cpp
  Main.cpp
  Record.cpp
  SetTheory.cpp
  StringMatcher.cpp
  TableGenBackend.cpp
  TableGenBackendSkeleton.cpp
  TGLexer.cpp
  TGParser.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/TableGen
  )

if (BUILD_SHARED_LIBS)
  target_link_libraries(LLVMTableGen PUBLIC LLVMSupport)
else()
  target_link_libraries(LLVMTableGen INTERFACE LLVMSupportLite)
endif()
