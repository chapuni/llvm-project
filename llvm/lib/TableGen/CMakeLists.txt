if(LLVM_ENABLE_TABLEGEN_MODULARIZED)
  set(tablegen_type SHARED)
endif()

add_llvm_component_library(LLVMTableGen ${tablegen_type}
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
elseif(LLVM_ENABLE_TABLEGEN_MODULARIZED)
  target_sources(LLVMTableGen PRIVATE $<TARGET_OBJECTS:obj.LLVMSupportLite>)
  target_link_libraries(LLVMTableGen PRIVATE LLVMSupportLite)
else()
  target_link_libraries(LLVMTableGen INTERFACE LLVMSupportLite)
endif()
