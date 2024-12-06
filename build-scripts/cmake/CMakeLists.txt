cmake_minimum_required( VERSION 3.22 )

project( iscool-core VERSION 1.9.3 )

set( source_root "${CMAKE_CURRENT_SOURCE_DIR}/../.." )
set( required_boost_version 1.74.0 )
set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )
set( CMAKE_CXX_STANDARD 20 )

# Use the CMake config provided by Boost instead of the deprecated one
# provided by CMake.
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

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

# The order matters, a module may depend on a previously listed one.
set(all_modules
  collections
  containers
  contract
  functional
  locale
  memory
  any
  strings
  error
  log
  files
  iterators
  time
  profile
  json
  random
  signals
  monitoring
  schedule
  http
  i18n
  preferences
  resources
  audio
  net
  video
  wish
  style
  factory
  notification
  social
  system
)

if( TARGET_ANDROID )
  set(all_modules ${all_modules} jni)
elseif( TARGET_IOS )
  set(all_modules ${all_modules} ios)
endif()


set(ISCOOL_ENABLE_MODULES
  "${all_modules}"
  CACHE STRING
  "A list of modules to build. Default is to build all modules. Note that
  there is no dependency managenent here, so building a single module
  may fail because a required dependency is not built."
)

set(ISCOOL_DISABLE_MODULES
  ""
  CACHE STRING
  "A list of modules to skip."
)

foreach(module ${all_modules})
  list(FIND ISCOOL_ENABLE_MODULES "${module}" is_enabled)
  list(FIND ISCOOL_DISABLE_MODULES "${module}" is_disabled)

  if(NOT is_enabled EQUAL -1 AND is_disabled EQUAL -1)
    add_subdirectory( "modules/${module}" )
  else()
    message("Skipping iscool::${module} on user request.")
  endif()
endforeach()

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
