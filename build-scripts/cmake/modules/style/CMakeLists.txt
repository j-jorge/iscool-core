project( iscool-style )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME style
  FILES
  "declaration.cpp"
  "loader.cpp"
  "log_context.cpp"
  "setup.cpp"

  "detail/get_properties_pool.cpp"
  "detail/get_style_cache.cpp"
  "detail/loader_merge_path_list.cpp"
  "detail/merge_declarations.cpp"
  "detail/properties.cpp"
  "detail/properties_handle.cpp"
  "detail/set_property_from_json_value.cpp"
  "detail/shared_properties.cpp"
  "detail/shared_properties_pool_traits.cpp"

  "json/from_declaration.cpp"
  "json/to_declaration.cpp"

  LINK
  iscool_core
  iscool_json
  )

declare_iscool_library_test( NAME style
  FILES
  "declaration.cpp"
  "deep_mutate.cpp"

  "json/from_declaration.cpp"
  "json/to_declaration.cpp"
  )
