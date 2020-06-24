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

  target_include_directories(
    ${executable_name}
    PUBLIC
    ${google_test_INCLUDE_DIRS}
    )

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
    ${google_test_LIBRARIES}
    )

  if( ISCOOL_AUTO_RUN_TESTS )
    add_custom_command( TARGET ${executable_name}
      POST_BUILD
      COMMAND ${executable_name}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      )
  endif()
endfunction()
