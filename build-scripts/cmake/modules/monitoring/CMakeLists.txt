project( iscool-monitoring )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME monitoring
  FILES
  "instant_quality.cpp"
  "progress_monitor.cpp"

  LINK
  iscool_log
  iscool_signals
  )

declare_iscool_library_test( NAME monitoring
  FILES
  "instant_quality.cpp"
  "progress_monitor.cpp"
  "progress_tracker.cpp"
  "state_monitor.cpp"
  
  LINK
  iscool_testing
  )
