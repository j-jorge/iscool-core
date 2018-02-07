include( install )

function( install_dependency )

  cmake_parse_arguments( ARG
    ""
    ""
    "HEADERS;LIBRARIES;EXCLUDE"
    ${ARGN}
    )

  set( exclude )
  
  foreach( pattern ${ARG_EXCLUDE} )
    set( exclude ${exclude} PATTERN ${pattern} EXCLUDE )
  endforeach()
  
  message( "exclude ${exclude}" )

  if( ARG_HEADERS )
    install(
      DIRECTORY "${ARG_HEADERS}"
      DESTINATION ${header_install_dir}
      ${exclude}
      )
  endif()

  if( ARG_LIBRARIES )
    file( GLOB files "${ARG_LIBRARIES}/*.a" )
    
    install(
      FILES ${files}
      DESTINATION ${library_install_dir}
      )
  endif()
  
endfunction()
