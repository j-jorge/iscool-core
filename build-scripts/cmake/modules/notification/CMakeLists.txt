project( iscool-notification )

include( declare-iscool-library )

if( TARGET_ANDROID )
  
  set( files
    "android/service.cpp"
    )
  set( libraries iscool_jni )
  set( platform_arguments ANDROID )

elseif( TARGET_IOS )
  
  set( files
    "ios/service.mm"
    )
  set( libraries
    iscool_ios
    iscool_log
  )
  
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
