project( iscool-iterators )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME
  iterators

  TEST
  "back_emplace_iterator.cpp"
  "cycle_iterator.cpp"

  TEST_LINK
  "iscool_testing"
)
