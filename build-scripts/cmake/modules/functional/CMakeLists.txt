project( iscool-functional )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME
  functional

  TEST
  "identity.cpp"
)
