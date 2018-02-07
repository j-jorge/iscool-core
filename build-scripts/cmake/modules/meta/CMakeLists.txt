project( iscool-meta )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME
  meta

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
