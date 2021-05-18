if(NOT BUILD_SHARED_LIBS)
  set(tablegen_objs
    $<TARGET_OBJECTS:obj.LLVMSupport>
    $<TARGET_OBJECTS:obj.LLVMDemangle>
  )
endif()

add_llvm_component_library(LLVMTableGen SHARED
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

  ${tablegen_objs}

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/TableGen

  LINK_LIBS
  LLVMSupport
  )

if (BUILD_SHARED_LIBS)
  target_link_libraries(LLVMTableGen INTERFACE LLVMSupport)
endif()
