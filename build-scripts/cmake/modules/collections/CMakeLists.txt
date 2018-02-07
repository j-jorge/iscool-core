project( iscool-collection )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME
  collections

  TEST
  "append.cpp"
  "apply_permutation.cpp"
  "binary_search.cpp"
  "has_duplicates.cpp"
  "insert_all.cpp"
  "make_array.cpp"
  "member_view.cpp"
  "sort_permutation.cpp"

  TEST_LINK
  iscool_testing
)
