project( iscool-schedule )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME schedule
  FILES
  "delayed_call.cpp"
  "manual_scheduler.cpp"
  "scaled_timer.cpp"
  "setup.cpp"
  "task.cpp"
  "task_group.cpp"
  "time_bounded_for_each.cpp"
  "timer.cpp"
  "worker.cpp"

  "detail/call_later.cpp"
  "detail/delayed_call_manager.cpp"
  "detail/task_life_cycle.cpp"

  LINK
  iscool_log
  iscool_signals
  )

declare_iscool_library_test( NAME schedule
  FILES
  "async_function.cpp"
  "async_signal.cpp"
  "concurrent_delayed_call.cpp"
  "delayed_call.cpp"
  "manual_scheduler.cpp"
  "real_clock.cpp"
  "scaled_timer.cpp"
  "task_group.cpp"
  "time_bounded_for_each.cpp"
  "timer.cpp"
  "worker.cpp"

  "test/observable_task.cpp"

  LINK
  iscool_testing
  )
