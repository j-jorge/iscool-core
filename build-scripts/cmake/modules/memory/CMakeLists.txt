project( iscool-memory )

include( declare-iscool-library )

find_package(
  Boost ${required_boost_version} REQUIRED
  )

declare_iscool_interface_library(
  NAME memory

  LINK
  iscool_contract
  Boost::boost
  
  TEST
  "dynamic_pool.cpp"
  "make_unique.cpp"
  "pimpl.cpp"
  )
