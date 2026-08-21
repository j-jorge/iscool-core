project( iscool-http )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME http
  FILES
  "compose_url.cpp"
  "get_global_mockup.cpp"
  "mockup.cpp"
  "request_connection.cpp"
  "request_connection_pool.cpp"
  "send.cpp"
  "setup.cpp"
  "url_encode.cpp"

  "detail/request_handler.cpp"
  "detail/request_handler_pool.cpp"
  "detail/send_delegate.cpp"

  "json/send.cpp"

  LINK
  iscool_json
  iscool_memory
  iscool_monitoring
  iscool_schedule
  iscool_signals
  )

declare_iscool_library_test( NAME http
  FILES
  "compose_url.cpp"
  "send.cpp"
  "url_encode.cpp"

  "json/send.cpp"
  )
