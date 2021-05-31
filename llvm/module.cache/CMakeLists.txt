get_property(generator_targets GLOBAL PROPERTY LLVM_GENERATOR_TARGETS)
list(APPEND LLVM_COMMON_DEPENDS ${generator_targets})
list(REMOVE_ITEM LLVM_COMMON_DEPENDS stub_all)

get_property(generator_includes GLOBAL PROPERTY LLVM_GENERATOR_INCLUDES)
list(REMOVE_DUPLICATES generator_includes)
include_directories(${generator_includes})

set(module_dir ${CMAKE_BINARY_DIR}/module.cache)

get_directory_property(includes INCLUDE_DIRECTORIES)
list(PREPEND includes " ")
list(JOIN includes " -I" includes)

get_target_property(compile_flags llvm-config COMPILE_FLAGS)
get_target_property(compile_options llvm-config COMPILE_OPTIONS)
list(JOIN compile_options " " compile_options)

set(LLVM_SCAN_DEPS /home/admin/llvm/install/2libcxx/bin/clang-scan-deps)
set(cmake_to_generate ${CMAKE_CURRENT_BINARY_DIR}/modules.cmake)

string(TOUPPER "${CMAKE_BUILD_TYPE}" build_type_toupper)

execute_process(
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/genmodules.py
  ${cmake_to_generate}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/..
  ${module_dir}
  ${LLVM_SCAN_DEPS}
  ${LLVM_DEFINITIONS}
  ${includes}
  ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${build_type_toupper}} ${compile_flags} ${compile_options} ${CMAKE_CXX${CMAKE_CXX_STANDARD}_STANDARD_COMPILE_OPTION}

  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  RESULT_VARIABLE result
  )

if(NOT "${result}" STREQUAL "0")
  message(FATAL_ERROR "ERROR(${result})")
endif()

include(${cmake_to_generate})
