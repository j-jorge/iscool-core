include( prepend-string )
include( unity-build )

include( iscool-repository )
include( declare-iscool-library-test )
include( install )

function( declare_iscool_library )

  cmake_parse_arguments( ARG
    "ANDROID"
    "NAME"
    "FILES;INCLUDE;LINK;DEFINITIONS"
    ${ARGN}
    )

  set( lib_name "iscool_${ARG_NAME}" )
  iscool_module_source_root( lib_source_root ${ARG_NAME} )

  prepend_string( files "${lib_source_root}/" ${ARG_FILES} )
  make_compilation_unit( unit ${ARG_NAME} ${files} )

  add_library( ${lib_name} ${unit} )

  iscool_module_include_argument( lib_include ${ARG_NAME} )

  target_include_directories(
    ${lib_name}
    PUBLIC
    "${lib_include}"
    ${ARG_INCLUDE}
    )

  if( ARG_LINK )
    target_link_libraries(
      ${lib_name}
      PUBLIC
      ${ARG_LINK}
      )
  endif()

  if( ARG_DEFINITIONS )
    target_compile_definitions(
      ${lib_name}
      PRIVATE
      ${ARG_DEFINITIONS}
      )
  endif()
      
  if( ARG_ANDROID )
    iscool_module_android_root( android_root ${ARG_NAME} )
    install(
      DIRECTORY ${android_root}/
      DESTINATION ${android_install_dir}/iscool/core/${ARG_NAME} )
  endif()
  
  install( DIRECTORY ${lib_include}/iscool DESTINATION ${header_install_dir} )
  install( TARGETS ${lib_name} DESTINATION ${library_install_dir} )
endfunction()

function( declare_iscool_interface_library )

  cmake_parse_arguments( ARG
    ""
    "NAME"
    "INCLUDE;LINK;TEST;TEST_LINK"
    ${ARGN}
    )

  set( lib_name "iscool_${ARG_NAME}" )
  add_library( ${lib_name} INTERFACE )
  
  iscool_module_include_argument( lib_include ${ARG_NAME} )

  target_include_directories(
    ${lib_name}
    INTERFACE
    ${lib_include}
    ${ARG_INCLUDE}
    )
  
  if( ARG_LINK )
    target_link_libraries(
      ${lib_name}
      INTERFACE
      ${ARG_LINK}
      )
  endif()

  declare_iscool_library_test(
    NAME ${ARG_NAME}
    FILES ${ARG_TEST}
    LINK ${ARG_TEST_LINK}
    )

  install( DIRECTORY ${lib_include}/iscool DESTINATION ${header_install_dir} )
endfunction()
