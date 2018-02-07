project( iscool-signals )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME signals
  FILES
  "connection.cpp"
  "scoped_connection.cpp"
  "shared_connection.cpp"
  "shared_connection_set.cpp"
  "signal.cpp"
  "statistics_data.cpp"
  "statistics_sink.cpp"
  "detail/slot.cpp"
  "detail/statistics_function.cpp"
  LINK
  iscool_meta
  iscool_profile
  )

declare_iscool_library_test( NAME signals
  FILES
  "connection.cpp"
  "find_signal_type_from_tuple_element.cpp"
  "get_from_tuple_element.cpp"
  "one_shot_signal.cpp"
  "relay.cpp"
  "scoped_connection.cpp"
  "shared_connection.cpp"
  "shared_connection_set.cpp"
  "signal_collection.cpp"
  "signal.cpp"
  "signal_from_tuple_arguments.cpp"
  LINK
  iscool_testing
  )
