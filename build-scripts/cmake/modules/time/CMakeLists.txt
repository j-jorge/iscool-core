project( iscool-time )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME
  time

  TEST
  "backward_duration_to_unit_change.cpp"
  "days.cpp"
  "round.cpp"
)
