project( iscool-core )

include( declare-iscool-library )
include( declare-iscool-library-test )

find_package(
  Boost ${required_boost_version} REQUIRED
  )

declare_iscool_library( NAME core
  FILES
  "digits.cpp"
  "none.cpp"
  "optional.cpp"

  INCLUDE
  ${Boost_INCLUDE_DIRS}
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
