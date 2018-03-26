project( iscool-system )

include( declare-iscool-library )
include( declare-iscool-library-test )

set( files
  "application_events.cpp"
  "application_event_source.cpp"
  "capture_screen.cpp"
  "setup.cpp"

  "detail/capture_screen_delegate.cpp"
  "detail/capture_screen_signal_pool.cpp"
  )

if( TARGET_ANDROID )

  set( files
    ${files}
    "android/language_code.cpp"
    "android/send_to_background.cpp"

    "android/detail/device_time_milliseconds.cpp"
    )
  set( libraries iscool_jni )
  set( platform_arguments ANDROID )
  
elseif( TARGET_IOS )

  set( files
    ${files}
    "ios/language_code.mm"
    "ios/send_to_background.mm"

    "ios/detail/device_time_milliseconds.mm"
    )
  
else()

  set( files
    ${files}
    "language_code.cpp"
    "send_to_background.cpp"

    "detail/device_time_milliseconds.cpp"
    )    

endif()

declare_iscool_library( NAME system
  FILES
  ${files}
  
  LINK
  ${libraries}
  iscool_log
  iscool_memory
  iscool_signals

  ${platform_arguments}
  )

declare_iscool_library_test( NAME system
  FILES
  "application_events.cpp"
  "application_event_source.cpp"
  "capture_screen.cpp"
  LINK
  iscool_testing
  )
