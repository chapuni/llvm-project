set(LLVM_LINK_COMPONENTS
  TableGen
  )

set(LLVM_TARGET_DEFINITIONS Automata.td)

tablegen(LLVM AutomataTables.inc -gen-searchable-tables)
tablegen(LLVM AutomataAutomata.inc -gen-automata)
add_public_tablegen_target(AutomataTestTableGen)

add_llvm_unittest(TableGenTests
  CodeExpanderTest.cpp
  AutomataTest.cpp
  )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../utils/TableGen)
target_link_libraries(TableGenTests PRIVATE LLVMTableGenGlobalISel LLVMTableGen)

# Prepend LLVMTableGen
# FIXME: Tweak link_libs when other issues would happen.
if(TARGET llvm-tblgen-automata)
  target_link_options(TableGenTests PRIVATE "$<TARGET_LINKER_FILE:LLVMTableGen>")
endif()
