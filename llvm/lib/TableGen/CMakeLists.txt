add_llvm_component_library(LLVMTableGen
  OBJECT
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

target_link_libraries(LLVMTableGen PUBLIC LLVMSupport)

add_llvm_library(LLVMTableGenLite SHARED PARTIAL_SOURCES_INTENDED
  $<TARGET_OBJECTS:obj.LLVMTableGen>
  $<FILTER:$<TARGET_OBJECTS:obj.LLVMSupport>,INCLUDE,$<TARGET_PROPERTY:LLVMSupport,LLVMTableGenLite_sources_regex>>
  )

target_link_libraries(LLVMTableGenLite PRIVATE
  ${LLVM_PTHREAD_LIB}
  rt
  /usr/lib/x86_64-linux-gnu/libtinfo.so
  )
