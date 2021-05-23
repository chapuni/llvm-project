# LLVM_TARGET_DEFINITIONS must contain the name of the .td file to process.
# Extra parameters for `tblgen' may come after `ofn' parameter.
# Adds the name of the generated file to TABLEGEN_OUTPUT.

function(tablegen project ofn)
  # Validate calling context.
  if(NOT ${project}_TABLEGEN_EXE)
    message(FATAL_ERROR "${project}_TABLEGEN_EXE not set")
  endif()

  # Use depfile instead of globbing arbitrary *.td(s) for Ninja.
  if(CMAKE_GENERATOR STREQUAL "Ninja")
    # Make output path relative to build.ninja, assuming located on
    # ${CMAKE_BINARY_DIR}.
    # CMake emits build targets as relative paths but Ninja doesn't identify
    # absolute path (in *.d) as relative path (in build.ninja)
    # Note that tblgen is executed on ${CMAKE_BINARY_DIR} as working directory.
    file(RELATIVE_PATH ofn_rel
      ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${ofn})
    set(additional_cmdline
      -o ${ofn_rel}
      -d ${ofn_rel}.d
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      DEPFILE ${CMAKE_CURRENT_BINARY_DIR}/${ofn}.d
      )
    set(local_tds)
    set(global_tds)
  else()
    file(GLOB local_tds "*.td")
    file(GLOB_RECURSE global_tds "${LLVM_MAIN_INCLUDE_DIR}/llvm/*.td")
    set(additional_cmdline
      -o ${CMAKE_CURRENT_BINARY_DIR}/${ofn}
      )
  endif()

  if (IS_ABSOLUTE ${LLVM_TARGET_DEFINITIONS})
    set(LLVM_TARGET_DEFINITIONS_ABSOLUTE ${LLVM_TARGET_DEFINITIONS})
  else()
    set(LLVM_TARGET_DEFINITIONS_ABSOLUTE
      ${CMAKE_CURRENT_SOURCE_DIR}/${LLVM_TARGET_DEFINITIONS})
  endif()
  if (LLVM_ENABLE_DAGISEL_COV)
    list(FIND ARGN "-gen-dag-isel" idx)
    if( NOT idx EQUAL -1 )
      list(APPEND LLVM_TABLEGEN_FLAGS "-instrument-coverage")
    endif()
  endif()
  if (LLVM_ENABLE_GISEL_COV)
    list(FIND ARGN "-gen-global-isel" idx)
    if( NOT idx EQUAL -1 )
      list(APPEND LLVM_TABLEGEN_FLAGS "-instrument-gisel-coverage")
      list(APPEND LLVM_TABLEGEN_FLAGS "-gisel-coverage-file=${LLVM_GISEL_COV_PREFIX}all")
    endif()
  endif()
  # Comments are only useful for Debug builds. Omit them if the backend
  # supports it.
  if (NOT (uppercase_CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR
           uppercase_CMAKE_BUILD_TYPE STREQUAL "RELWITHDEBINFO"))
    list(FIND ARGN "-gen-dag-isel" idx)
    if (NOT idx EQUAL -1)
      list(APPEND LLVM_TABLEGEN_FLAGS "-omit-comments")
    endif()
  endif()

  # MSVC can't support long string literals ("long" > 65534 bytes)[1], so if there's
  # a possibility of generated tables being consumed by MSVC, generate arrays of
  # char literals, instead. If we're cross-compiling, then conservatively assume
  # that the source might be consumed by MSVC.
  # [1] https://docs.microsoft.com/en-us/cpp/cpp/compiler-limits?view=vs-2017
  if (MSVC AND project STREQUAL LLVM)
    list(APPEND LLVM_TABLEGEN_FLAGS "--long-string-literals=0")
  endif()
  if (CMAKE_GENERATOR MATCHES "Visual Studio")
    # Visual Studio has problems with llvm-tblgen's native --write-if-changed
    # behavior. Since it doesn't do restat optimizations anyway, just don't
    # pass --write-if-changed there.
    set(tblgen_change_flag)
  else()
    set(tblgen_change_flag "--write-if-changed")
  endif()

  # We need both _TABLEGEN_TARGET and _TABLEGEN_EXE in the  DEPENDS list
  # (both the target and the file) to have .inc files rebuilt on
  # a tablegen change, as cmake does not propagate file-level dependencies
  # of custom targets. See the following ticket for more information:
  # https://cmake.org/Bug/view.php?id=15858
  # The dependency on both, the target and the file, produces the same
  # dependency twice in the result file when
  # ("${${project}_TABLEGEN_TARGET}" STREQUAL "${${project}_TABLEGEN_EXE}")
  # but lets us having smaller and cleaner code here.
  get_directory_property(tblgen_includes INCLUDE_DIRECTORIES)
  list(TRANSFORM tblgen_includes PREPEND -I)

  if (TARGET "${${project}_TABLEGEN_EXE}" AND "${ARGN}" MATCHES "^--?gen-")
    list(GET ARGN 0 arg0)
    string(REGEX REPLACE "^--?gen-(.+)" "${${project}_TABLEGEN_EXE}-\\1" plugin_name "${arg0}")
    if (NOT TARGET "${plugin_name}")
      set(plugin_name)
    endif()
  endif()

  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${ofn}
    COMMAND ${${project}_TABLEGEN_EXE} ${ARGN} -I ${CMAKE_CURRENT_SOURCE_DIR}
    ${tblgen_includes}
    ${LLVM_TABLEGEN_FLAGS}
    ${LLVM_TARGET_DEFINITIONS_ABSOLUTE}
    ${tblgen_change_flag}
    ${additional_cmdline}
    # The file in LLVM_TARGET_DEFINITIONS may be not in the current
    # directory and local_tds may not contain it, so we must
    # explicitly list it here:
    DEPENDS ${${project}_TABLEGEN_TARGET} ${${project}_TABLEGEN_EXE}
      ${local_tds} ${global_tds}
      ${plugin_name}
    ${LLVM_TARGET_DEFINITIONS_ABSOLUTE}
    COMMENT "Building ${ofn}..."
    )

  # `make clean' must remove all those generated files:
  set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${ofn})

  set(TABLEGEN_OUTPUT ${TABLEGEN_OUTPUT} ${CMAKE_CURRENT_BINARY_DIR}/${ofn} PARENT_SCOPE)
  set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${ofn} PROPERTIES
    GENERATED 1)
endfunction()

# Push ${target} if ${TABLEGEN_OUTPUT}s in INCLUDE_DIRECTORIES
function(llvm_push_generator_target)
  foreach(inc ${tblgen_includes})
    foreach(fn ${TABLEGEN_OUTPUT})
      file(RELATIVE_PATH rfn ${inc} ${fn})
      if(NOT "${rfn}" MATCHES "^[.][.]")
        set_property(GLOBAL APPEND PROPERTY LLVM_GENERATOR_TARGETS ${target})
        return()
      endif()
    endforeach()
  endforeach()
endfunction()

# Creates a target for publicly exporting tablegen dependencies.
function(add_public_tablegen_target target)
  if(NOT TABLEGEN_OUTPUT)
    message(FATAL_ERROR "Requires tablegen() definitions as TABLEGEN_OUTPUT.")
  endif()
  add_custom_target(${target}
    DEPENDS ${TABLEGEN_OUTPUT})
  if(LLVM_COMMON_DEPENDS)
    add_dependencies(${target} ${LLVM_COMMON_DEPENDS})
  endif()
  set_target_properties(${target} PROPERTIES FOLDER "Tablegenning")
  set(LLVM_COMMON_DEPENDS ${LLVM_COMMON_DEPENDS} ${target} PARENT_SCOPE)

  # Prepend
  get_directory_property(tblgen_includes INCLUDE_DIRECTORIES)
  set_property(GLOBAL APPEND PROPERTY LLVM_GENERATOR_INCLUDES ${tblgen_includes})

  # Push target for modules if the output is in includes
  llvm_push_generator_target()

endfunction()

function(add_tablegen_impl target)
  set(LLVM_LINK_COMPONENTS TableGen ${LLVM_LINK_COMPONENTS})

  if(NOT XCODE)
    # CMake doesn't let compilation units depend on their dependent libraries on some generators.
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
      set(LLVM_ENABLE_OBJLIB ON)
    endif()
    if (NOT ${LLVM_ENABLE_TABLEGEN_MODULARIZED})
      set(LLVM_ENABLE_OBJLIB ON)
    endif()
  endif()

  cmake_parse_arguments(T
    "PARTIAL_SOURCES_INTENDED"
    ""
    ""
    ${ARGN})

  set(residual_args ${T_UNPARSED_ARGUMENTS})
  list(FIND residual_args MODULE midx)
  list(SUBLIST residual_args 0 ${midx} t_args)
  while (${midx} GREATER_EQUAL 0)
    list(SUBLIST residual_args ${midx} -1 residual_args)
    list(REMOVE_AT residual_args 0) # "MODULE"
    list(FIND residual_args MODULE midx)
    list(SUBLIST residual_args 0 ${midx} m_args) # midx may be -1
    list(GET m_args 0 m_name)
    list(REMOVE_AT m_args 0)
    set(m_target "${target}-${m_name}")
    cmake_parse_arguments(M
      "SHARED"
      ""
      "DEPENDS"
      ${m_args})

    if (NOT ${LLVM_ENABLE_TABLEGEN_MODULARIZED})
      list(JOIN M_UNPARSED_ARGUMENTS "," m_items)
      list(APPEND m_module_args "${m_name}=${m_items}")
      list(APPEND t_args ${M_UNPARSED_ARGUMENTS})
      continue()
    endif()

    if(${M_SHARED})
      set(m_type SHARED)
    else()
      set(m_type MODULE)
    endif()
    add_llvm_library(${m_target} ${m_type}
      ${M_UNPARSED_ARGUMENTS}
      PARTIAL_SOURCES_INTENDED
      )
    set_target_properties(${m_target} PROPERTIES
      PREFIX ""
      )
    set(m_deps)
    foreach(d ${M_DEPENDS})
      if(NOT TARGET "${target}-${d}")
        message(FATAL_ERROR "${m_name}: Unknown depend: (${target}-)${d}")
      endif()
      list(APPEND m_deps "${target}-${d}")
    endforeach()
    if(NOT m_deps)
      list(APPEND m_deps LLVMTableGen)
    endif()
    target_link_libraries(${m_target} PUBLIC ${m_deps})
    list(APPEND modules ${m_target})
  endwhile()

  add_llvm_executable(${target}
    DISABLE_LLVM_LINK_LLVM_DYLIB
    PARTIAL_SOURCES_INTENDED
    ${t_args})
  message("<${t_args}>")

  # Check and suggest deps
  if (TARGET obj.${target} AND NOT "${m_module_args}" STREQUAL "")
    set(tblgen_all_args
      COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/xxx.py
      ${CMAKE_CURRENT_BINARY_DIR}
      "$<JOIN:$<TARGET_OBJECTS:obj.${target}>,$<COMMA>>"
      ${m_module_args}
      DEPENDS obj.${target}
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      )
  endif()

  set(tblgen_all "${target}-all")
  add_custom_target(${tblgen_all} ${tblgen_all_args})
  add_dependencies(${tblgen_all} ${target} ${modules})

  if(NOT ${T_PARTIAL_SOURCES_INTENDED})
    llvm_check_source_file_list()
  endif()
endfunction()

macro(add_tablegen target project)
  add_tablegen_impl(${target} ${ARGN})

  set(${project}_TABLEGEN "${target}" CACHE
      STRING "Native TableGen executable. Saves building one when cross-compiling.")

  # Effective tblgen executable to be used:
  set(${project}_TABLEGEN_EXE ${${project}_TABLEGEN} PARENT_SCOPE)
  set(${project}_TABLEGEN_TARGET ${${project}_TABLEGEN} PARENT_SCOPE)

  if(LLVM_USE_HOST_TOOLS)
    if( ${${project}_TABLEGEN} STREQUAL "${target}" )
      # The NATIVE tablegen executable *must* depend on the current target one
      # otherwise the native one won't get rebuilt when the tablgen sources
      # change, and we end up with incorrect builds.
      build_native_tool(${target} ${project}_TABLEGEN_EXE DEPENDS ${target})
      set(${project}_TABLEGEN_EXE ${${project}_TABLEGEN_EXE} PARENT_SCOPE)

      add_custom_target(${project}-tablegen-host DEPENDS ${${project}_TABLEGEN_EXE})
      set(${project}_TABLEGEN_TARGET ${project}-tablegen-host PARENT_SCOPE)

      # Create an artificial dependency between tablegen projects, because they
      # compile the same dependencies, thus using the same build folders.
      # FIXME: A proper fix requires sequentially chaining tablegens.
      if (NOT ${project} STREQUAL LLVM AND TARGET ${project}-tablegen-host AND
          TARGET LLVM-tablegen-host)
        add_dependencies(${project}-tablegen-host LLVM-tablegen-host)
      endif()

      # If we're using the host tablegen, and utils were not requested, we have no
      # need to build this tablegen.
      if ( NOT LLVM_BUILD_UTILS )
        set_target_properties(${target} PROPERTIES EXCLUDE_FROM_ALL ON)
      endif()
    endif()
  endif()

  if ((${project} STREQUAL LLVM OR ${project} STREQUAL MLIR) AND NOT LLVM_INSTALL_TOOLCHAIN_ONLY AND LLVM_BUILD_UTILS)
    set(export_to_llvmexports)
    if(${target} IN_LIST LLVM_DISTRIBUTION_COMPONENTS OR
        NOT LLVM_DISTRIBUTION_COMPONENTS)
      set(export_to_llvmexports EXPORT LLVMExports)
    endif()

    install(TARGETS ${target}
            ${export_to_llvmexports}
            COMPONENT ${target}
            RUNTIME DESTINATION ${LLVM_TOOLS_INSTALL_DIR})
    if(NOT LLVM_ENABLE_IDE)
      add_llvm_install_targets("install-${target}"
                               DEPENDS ${target}
                               COMPONENT ${target})
    endif()
  endif()
  set_property(GLOBAL APPEND PROPERTY LLVM_EXPORTS ${target})
endmacro()
