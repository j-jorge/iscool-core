project( iscool-log )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME log
  FILES
  "context.cpp"
  "message_delegates.cpp"
  "message_delegates_registry.cpp"
  "setup.cpp"
  "detail/get_message_dispatcher.cpp"
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
  )

declare_iscool_library_test( NAME log
  FILES
  "context.cpp"
  "log.cpp"
  "nature/nature.cpp"
  )
