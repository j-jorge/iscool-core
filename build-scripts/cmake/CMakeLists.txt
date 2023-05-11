cmake_minimum_required( VERSION 3.1 )

project( iscool-core VERSION 1.8.0 )

set( source_root "${CMAKE_CURRENT_SOURCE_DIR}/../.." )
set( required_boost_version 1.58.0 )
set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )
set( CMAKE_CXX_STANDARD 17 )

include( platform )
include( boost )

if( NOT TARGET_ANDROID AND NOT TARGET_IOS AND NOT DEFINED ISCOOL_TEST_ENABLED )
  set( ISCOOL_TEST_ENABLED 1 )
endif()

if( ISCOOL_TEST_ENABLED )
  include( google-test )
endif()

option(
  ISCOOL_CORE_WITH_CMAKE_PACKAGE
  "Generate and install cmake package files" OFF
  )
option(
  ISCOOL_AUTO_RUN_TESTS
  "Run the unit tests during the build." ON
  )

if( ISCOOL_CORE_WITH_CMAKE_PACKAGE )
  set( iscool_core_export EXPORT iscool-core )
endif()

include_directories( ${CMAKE_PREFIX_PATH}/include )
link_directories( ${CMAKE_PREFIX_PATH}/lib )

add_subdirectory( "testing/test" )

add_subdirectory( "modules/core" )
add_subdirectory( "modules/meta" )

add_subdirectory( "modules/collections" )
add_subdirectory( "modules/containers" )
add_subdirectory( "modules/contract" )
add_subdirectory( "modules/functional" )
add_subdirectory( "modules/locale" )
add_subdirectory( "modules/memory" )
add_subdirectory( "modules/any" )
add_subdirectory( "modules/strings" )
add_subdirectory( "modules/error" )
add_subdirectory( "modules/log" )
add_subdirectory( "modules/files" )
add_subdirectory( "modules/iterators" )
add_subdirectory( "modules/time" )
add_subdirectory( "modules/profile" )
add_subdirectory( "modules/json" )
add_subdirectory( "modules/random" )
add_subdirectory( "modules/signals" )
add_subdirectory( "modules/monitoring" )
add_subdirectory( "modules/schedule" )
add_subdirectory( "modules/http" )
add_subdirectory( "modules/i18n" )
add_subdirectory( "modules/preferences" )
add_subdirectory( "modules/resources" )
add_subdirectory( "modules/audio" )
add_subdirectory( "modules/net" )
add_subdirectory( "modules/video" )
add_subdirectory( "modules/wish" )
add_subdirectory( "modules/style" )
add_subdirectory( "modules/factory" )

if( TARGET_ANDROID )
  add_subdirectory( "modules/jni" )
elseif( TARGET_IOS )
  add_subdirectory( "modules/ios" )
endif()

add_subdirectory( "modules/notification" )
add_subdirectory( "modules/social" )
add_subdirectory( "modules/system" )

option(
  ISCOOL_CORE_WITH_APPS
  "Generate and install the apps" OFF
  )

if( NOT TARGET_ANDROID AND NOT TARGET_IOS AND ISCOOL_CORE_WITH_APPS )
  add_subdirectory( "apps/style-merger" )
endif()

if( ISCOOL_CORE_WITH_CMAKE_PACKAGE )
  add_subdirectory( "package" )
endif()
