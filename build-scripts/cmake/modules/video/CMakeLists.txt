project( iscool-video )

include( declare-iscool-library )

find_library( avcodec_library avcodec )
find_library( avformat_library avformat )
find_library( avutil_library avutil )
find_library( swscale_library swscale )

if( NOT avcodec_library
    OR NOT avformat_library
    OR NOT avutil_library
    OR NOT swscale_library )

  message(
    WARNING
    "FFmpeg libraries not found. Skipping iscool::video module."
    )
  return()
endif()

find_package( ZLIB REQUIRED )
find_package( Threads REQUIRED )

declare_iscool_library( NAME video
  FILES
  "decoder.cpp"
  "optional.cpp"

  LINK
  iscool_schedule
  swscale
  avformat
  avcodec
  avutil
  ZLIB::ZLIB
  Threads::Threads
  )
