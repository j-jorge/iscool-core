project( iscool-core )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME core
  FILES
  "digits.cpp"
  "none.cpp"
  "optional.cpp"
  )

declare_iscool_library_test( NAME core
  FILES
  "context.cpp"
  "copy.cpp"
  "digits.cpp"
  "enum_equals.cpp"
  "optional.cpp"
  "optional_or_else.cpp"
  LINK
  iscool_testing
  )
