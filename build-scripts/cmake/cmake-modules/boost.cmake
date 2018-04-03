include( platform )

if( USE_DEFAULT_BOOST OR NOT ( TARGET_ANDROID OR TARGET_IOS ) )
  find_package( Boost 1.58 REQUIRED filesystem system )
  return()
endif()

if( TARGET_ANDROID )
  include( boost-android )
elseif( TARGET_IOS )
  include( boost-ios )
endif()
