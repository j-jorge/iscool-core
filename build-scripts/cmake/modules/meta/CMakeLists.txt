project( iscool-meta )

include( declare-iscool-library )

find_package(
  Boost ${required_boost_version} REQUIRED
  )

declare_iscool_interface_library(
  NAME
  meta

  INCLUDE
  ${Boost_INCLUDE_DIRS}

  TEST
  "constant_equality.cpp"
  "contains.cpp"
  "declare_namespaces.cpp"
  "function_from_signature.cpp"
  "member_comparator.cpp"
  "member_constant_equality.cpp"
  "new_from_tuple.cpp"
  "reference_namespaces.cpp"
  "toggle_field.cpp"
  "type_index.cpp"
  "underlying_type.cpp"
)
