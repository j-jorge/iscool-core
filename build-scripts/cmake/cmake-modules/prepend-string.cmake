macro( prepend_string DEST PREFIX )
  set( ${DEST} "" )

  foreach( SUFFIX ${ARGN} )
    set( ${DEST} "${${DEST}}" "${PREFIX}${SUFFIX}" )
  endforeach()
endmacro()
