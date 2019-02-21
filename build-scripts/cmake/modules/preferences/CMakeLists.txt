project( iscool-preferences )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME preferences
  FILES
  "declare_global_bool_property.cpp"
  "declare_global_float_property.cpp"
  "declare_global_int_property.cpp"
  "declare_global_string_property.cpp"
  "destroy_global_bool_property.cpp"
  "destroy_global_float_property.cpp"
  "destroy_global_int_property.cpp"
  "destroy_global_string_property.cpp"
  "get_global_bool_property.cpp"
  "get_global_float_property.cpp"
  "get_global_int_property.cpp"
  "get_global_string_property.cpp"
  "local_preferences.cpp"
  "log_context.cpp"
  "property_deserializer.cpp"
  "property_map_to_json.cpp"
  "set_global_properties.cpp"
  "store.cpp"

  "detail/global_deserializer.cpp"
  "detail/global_properties.cpp"
  "detail/local_preferences_from_json.cpp"
  "detail/property.cpp"

  LINK
  iscool_containers
  iscool_json
  iscool_schedule
  iscool_signals
  )

declare_iscool_library_test( NAME preferences
  FILES
  "global_properties.cpp"
  "property_deserializer.cpp"
  "store.cpp"

  "detail/local_preferences_from_json.cpp"

  LINK
  iscool_testing
  )
