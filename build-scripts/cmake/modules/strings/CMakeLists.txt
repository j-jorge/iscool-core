project( iscool-strings )

include( declare-iscool-library )
include( declare-iscool-library-test )

find_package(
  Boost ${required_boost_version} REQUIRED
  )

declare_iscool_library( NAME strings
  FILES
  "dynamic_hash.cpp"
  "hash.cpp"
  "string_hash.cpp"

  LINK
  iscool_memory
  Boost::boost
  )

declare_iscool_library_test( NAME strings
  FILES
  "str_const.cpp"
  "string_hash.cpp"
  "vector_to_string.cpp"
  )
