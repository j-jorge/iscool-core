include( platform )

option(
  ENABLE_COMPILATION_UNITS
  "Merge all source files together to reduce the number of times the compiler\
 is invoked."
  ON
  )

function( make_compilation_unit unit_file name )

  if(NOT ENABLE_COMPILATION_UNITS)
    set( ${unit_file} ${ARGN} PARENT_SCOPE )
    return()
  endif()
  
  set( temporary_unit "${PROJECT_BINARY_DIR}/${name}.unit.tmp" )
  file( REMOVE "${temporary_unit}" )

  foreach( f ${ARGN} )
    file( APPEND "${temporary_unit}" "#include \"${f}\"\n" )
  endforeach()

  if( TARGET_IOS )
    set( extension "mm" )
  else()
    set( extension "cpp" )
  endif()

  set( final_unit "${PROJECT_BINARY_DIR}/${name}.unit.${extension}" )

  execute_process( COMMAND ${CMAKE_COMMAND}
    -E compare_files
    "${temporary_unit}"
    "${final_unit}"
    RESULT_VARIABLE need_update
    OUTPUT_QUIET
    ERROR_QUIET
    )

  if( need_update )
    execute_process( COMMAND ${CMAKE_COMMAND}
      -E copy
      "${temporary_unit}"
      "${final_unit}"
      )
  endif()

  file( REMOVE "${temporary_unit}" )

  set( ${unit_file} ${final_unit} PARENT_SCOPE )
endfunction()
