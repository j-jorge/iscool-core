if( NOT ISCOOL_TEST_ENABLED )

  function( declare_iscool_library_test )
  endfunction()
  
  return()
endif()
  
include( iscool-repository )
include( prepend-string )
include( unity-build )

function( declare_iscool_library_test )

  cmake_parse_arguments( ARG
    ""
    "NAME"
    "FILES;LINK"
    ${ARGN}
    )

  set( executable_name "iscool_${ARG_NAME}_test" )
  iscool_module_test_source_root( lib_source_root ${ARG_NAME} )

  prepend_string( files "${lib_source_root}/" ${ARG_FILES} )
  make_compilation_unit( unit ${ARG_NAME}-test ${files} )

  add_executable( ${executable_name} ${unit} )

  iscool_module_test_include_argument( executable_include ${ARG_NAME} )

  if( EXISTS ${executable_include} )
    target_include_directories(
      ${executable_name}
      PUBLIC
      ${executable_include}
      )
  endif()

  target_link_libraries( ${executable_name}
    iscool_${ARG_NAME}
    ${ARG_LINK}
    gtest
    gtest_main
    )

  add_custom_command( TARGET ${executable_name}
    POST_BUILD
    COMMAND ${executable_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endfunction()
