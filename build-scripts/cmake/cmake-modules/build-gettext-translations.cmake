include( FindGettext )

function( build_gettext_translations )

  cmake_parse_arguments( ARG
    ""
    "TARGET;OUTPUT_DIR"
    "FILES"
    ${ARGN}
    )

  if( ARG_OUTPUT_DIR )
    file( MAKE_DIRECTORY ${ARG_OUTPUT_DIR} )
  else()
    set( ARG_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR} )
  endif()
  
  foreach( po_file ${ARG_FILES} )
    get_filename_component( po_file_absolute ${po_file} ABSOLUTE )
    get_filename_component( language_code ${po_file} NAME_WE )
    set( mo_file ${ARG_OUTPUT_DIR}/${language_code}.mo )

    add_custom_command(
      TARGET ${ARG_TARGET}
      PRE_BUILD
      COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${mo_file} ${po_file_absolute}
      DEPENDS ${po_file_absolute}
      )
  endforeach()

endfunction()
