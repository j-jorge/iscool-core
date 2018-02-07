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

if( CMAKE_SYSTEM_NAME STREQUAL "Android" )
  set( files
    ${files}
    android/language_code.cpp
    android/send_to_background.cpp
    )
  set( libraries iscool_jni )
  set( platform_arguments ANDROID )
else()
  set( files
    ${files}
    "language_code.cpp"
    "send_to_background.cpp"
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
  )
