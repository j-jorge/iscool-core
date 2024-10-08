project( iscool-log )

include( declare-iscool-library )
include( declare-iscool-library-test )

if( NOT TARGET_IOS AND NOT TARGET_ANDROID )
  set( iscool_log_definitions ISCOOL_LOG_PRETTY_PRINT=1 )
endif()

find_package( Threads )

declare_iscool_library( NAME log
  FILES
  "add_file_sink.cpp"
  "context.cpp"
  "enable_console_log.cpp"
  "message_delegates.cpp"
  "message_delegates_registry.cpp"
  "setup.cpp"

  "detail/get_message_dispatcher.cpp"
  "detail/logger_thread.cpp"
  "detail/message_dispatcher.cpp"
  "detail/prettify.cpp"
  "detail/print_to_console.cpp"
  "nature/debug.cpp"
  "nature/error.cpp"
  "nature/info.cpp"
  "nature/nature.cpp"
  "nature/warning.cpp"

  LINK
  iscool_core
  iscool_error
  iscool_strings
  Threads::Threads

  DEFINITIONS
  ${iscool_log_definitions}

  ANDROID
  )

declare_iscool_library_test( NAME log
  FILES
  "context.cpp"
  "log.cpp"
  "nature/nature.cpp"
  )
