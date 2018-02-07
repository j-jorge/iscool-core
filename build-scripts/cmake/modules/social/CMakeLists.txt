project( iscool-social )

include( declare-iscool-library )

set( files
  "link_service.cpp"
  "service.cpp"
  "share_service.cpp"
  )

if( CMAKE_SYSTEM_NAME STREQUAL "Android" )
  set( files
    ${files}
    "android/link_service.cpp"
    "android/share_service.cpp"
    )
  set( libraries iscool_jni )
  set( platform_arguments ANDROID )
else()
  set( files
    ${files}
    "detail/mockup_link_service.cpp"
    "detail/mockup_share_service.cpp"
    )    
  set( libraries
    iscool_log
    )
endif()

declare_iscool_library( NAME social
  FILES
  ${files}
  
  LINK
  ${libraries}

  ${platform_arguments}
  )
