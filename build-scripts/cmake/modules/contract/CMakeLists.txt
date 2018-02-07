project( iscool-contract )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME contract

  TEST
  "verify.cpp"
  "verify_not_null.cpp"

  TEST_LINK
  iscool_testing
  )
