project( iscool-strings )

include( declare-iscool-library )
include( declare-iscool-library-test )

find_package(
  Boost ${required_boost_version} REQUIRED
  )

declare_iscool_library( NAME strings
  FILES
  "dynamic_hash.cpp"
  "string_hash.cpp"
  "detail/formatter.cpp"
  "detail/formatter_bridge.cpp"

  INCLUDE
  ${Boost_INCLUDE_DIRS}
  
  LINK
  iscool_memory
  ${Boost_LIBRARIES}
  )

declare_iscool_library_test( NAME strings
  FILES
  "format.cpp"
  "str_const.cpp"
  "string_hash.cpp"
  "vector_to_string.cpp"
  )
