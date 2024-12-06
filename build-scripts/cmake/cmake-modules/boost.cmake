include( platform )

if( USE_DEFAULT_BOOST OR NOT ( TARGET_ANDROID OR TARGET_IOS ) )
  find_package( Boost ${required_boost_version} REQUIRED system )
  return()
endif()

if( TARGET_ANDROID )
  include( boost-android )
elseif( TARGET_IOS )
  include( boost-ios )
endif()
