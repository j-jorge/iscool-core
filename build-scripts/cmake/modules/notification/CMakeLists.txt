project( iscool-notification )

include( declare-iscool-library )

if( CMAKE_SYSTEM_NAME STREQUAL "Android" )
  set( files
    "android/service.cpp"
    )
  set( libraries iscool_jni )
  set( platform_arguments ANDROID )
else()
  set( files
    "detail/mockup_service.cpp"
    )
  set( libraries
    iscool_log
    )
endif()

declare_iscool_library( NAME notification
  FILES
  ${files}
  
  LINK
  ${libraries}

  ${platform_arguments}
  )
