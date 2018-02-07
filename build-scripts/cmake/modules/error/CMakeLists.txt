project( iscool-error )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME error
  FILES
  "optional.cpp"
  "synopsis.cpp"

  LINK
  iscool_core
  )

declare_iscool_library_test( NAME error
  FILES
  "synopsis.cpp"
  )
