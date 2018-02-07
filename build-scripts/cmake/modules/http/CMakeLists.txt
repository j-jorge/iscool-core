project( iscool-http )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME http
  FILES
  "compose_url.cpp"
  "get_global_mockup.cpp"
  "mockup.cpp"
  "request.cpp"
  "response.cpp"
  "send.cpp"
  "service_statistics.cpp"
  "setup.cpp"
  "url_encode.cpp"

  "detail/get_service_statistics.cpp"
  "detail/request_handler.cpp"
  "detail/request_handler_pool.cpp"
  "detail/send_delegate.cpp"

  "json/send.cpp"
  
  LINK
  iscool_json
  iscool_monitoring
  iscool_schedule
  iscool_signals
  )

declare_iscool_library_test( NAME http
  FILES
  "compose_url.cpp"
  "request.cpp"
  "response.cpp"
  "send.cpp"
  "service_statistics.cpp"
  "url_encode.cpp"

  "json/send.cpp"
  )
