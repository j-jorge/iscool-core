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
    "android/application_id.cpp"
    "android/application_version.cpp"
    "android/device_date.cpp"
    "android/device_model.cpp"
    "android/language_code.cpp"
    "android/os_name.cpp"
    "android/os_version.cpp"
    "android/send_mail.cpp"
    "android/send_to_background.cpp"

    "android/detail/device_time_milliseconds.cpp"

    "detail/haptic_feedback_mockup.cpp"
    )
  set( libraries iscool_jni )
  set( platform_arguments ANDROID )
  
elseif( TARGET_IOS )

  set( files
    ${files}
    "device_date.cpp"
    
    "ios/application_id.mm"
    "ios/application_version.mm"
    "ios/device_model.mm"
    "ios/haptic_feedback.mm"
    "ios/language_code.mm"
    "ios/os_name.mm"
    "ios/os_version.mm"
    "ios/send_mail.mm"
    "ios/send_to_background.mm"

    "ios/detail/device_time_milliseconds.mm"
    )

  set( libraries
    iscool_ios
    iscool_schedule
    )
  
else()

  set( files
    ${files}

    "application_id.cpp"
    "application_version.cpp"
    "device_date.cpp"
    "device_model.cpp"
    "language_code.cpp"
    "os_name.cpp"
    "os_version.cpp"
    "send_mail.cpp"
    "send_to_background.cpp"

    "detail/device_time_milliseconds.cpp"
    "detail/haptic_feedback_mockup.cpp"
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
