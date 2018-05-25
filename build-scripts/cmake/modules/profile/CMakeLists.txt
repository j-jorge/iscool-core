project( iscool-profile )

include( declare-iscool-library )
include( declare-iscool-library-test )

find_package(
  Boost ${required_boost_version} REQUIRED
  )

declare_iscool_library( NAME profile
  FILES
  "profile_data.cpp"
  "profiler.cpp"
  "scoped_profiler.cpp"
  "setup.cpp"
  "detail/output_function.cpp"

  LINK
  iscool_core
  iscool_time
  Boost::boost
  )

declare_iscool_library_test( NAME profile
  FILES
  "profiler.cpp"
  "scoped_profiler.cpp"

  LINK
  iscool_testing
  )
