project( iscool-random )

include( declare-iscool-library )
include( declare-iscool-library-test )

find_package(
  Boost ${required_boost_version} REQUIRED
  )

declare_iscool_library( NAME random
  FILES
  "distinct_random.cpp"
  "rand.cpp"

  LINK
  Boost::boost
  )

declare_iscool_library_test( NAME random
  FILES
  "distinct_random.cpp"
  "generator.cpp"
  "queue.cpp"

  LINK
  iscool_testing
  )
