get_property(generator_targets GLOBAL PROPERTY LLVM_GENERATOR_TARGETS)
list(APPEND LLVM_COMMON_DEPENDS ${generator_targets})
list(REMOVE_ITEM LLVM_COMMON_DEPENDS stub_all)

get_property(generator_includes GLOBAL PROPERTY LLVM_GENERATOR_INCLUDES)
list(REMOVE_DUPLICATES generator_includes)
include_directories(${generator_includes})

include(${CMAKE_BINARY_DIR}/xxx/mods.cmake)
