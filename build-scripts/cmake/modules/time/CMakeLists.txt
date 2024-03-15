project( iscool-time )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library(
  NAME time

  FILES
  "setup.cpp"
  "detail/monotonic_time_source.cpp"
  "detail/time_source.cpp"
)

declare_iscool_library_test(
  NAME time

  FILES
  "backward_duration_to_unit_change.cpp"
  "days.cpp"
  "round.cpp"
  "time_source.cpp"
)
