project( iscool-containers )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME
  containers

  LINK
  iscool_core
  iscool_meta
  
  TEST
  "heterogeneous_map.cpp"
)
