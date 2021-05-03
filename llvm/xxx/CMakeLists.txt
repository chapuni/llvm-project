list(REMOVE_ITEM LLVM_COMMON_DEPENDS stub_all)

include_directories(${CMAKE_BINARY_DIR}/tools/clang/include ${CMAKE_SOURCE_DIR}/../clang/include)

include(${CMAKE_BINARY_DIR}/xxx/mods.cmake)
