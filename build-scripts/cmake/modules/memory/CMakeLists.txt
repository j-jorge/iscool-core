project( iscool-memory )

include( declare-iscool-library )

find_package(
  Boost ${required_boost_version} REQUIRED COMPONENTS thread system
  )

declare_iscool_interface_library(
  NAME memory

  INCLUDE
  ${Boost_INCLUDE_DIRS}
  
  LINK
  iscool_contract
  ${Boost_LIBRARIES}
  
  TEST
  "dynamic_pool.cpp"
  "make_unique.cpp"
  "pimpl.cpp"
  )
