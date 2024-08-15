project( iscool-social )

include( declare-iscool-library )

set( files
  "link_service.cpp"
  "service.cpp"
  "share_service.cpp"
  )

if( TARGET_ANDROID )
  
  set( files
    ${files}
    "android/link_service.cpp"
    "android/share_service.cpp"
    )
  set(
    libraries
    iscool_files
    iscool_jni
    )
  set( platform_arguments ANDROID )
  
elseif( TARGET_IOS )
  
  set( files
    ${files}
    "ios/link_service.mm"
    "ios/present_activity_view_controller.mm"
    "ios/share_service.mm"
    )
  set( libraries
    iscool_ios
    )

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

if( TARGET_ANDROID )
  target_compile_definitions(
    iscool_social PUBLIC ISCOOL_TARGET_ANDROID=1
  )
endif()
