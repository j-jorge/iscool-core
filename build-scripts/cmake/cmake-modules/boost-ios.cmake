if( Boost_INCLUDE_DIR )
  message(
    "Skipping build for Boost library. Boost_INCLUDE_DIR=${Boost_INCLUDE_DIR}"
    )
  return()
endif()

project( boost-ios NONE )

include( DownloadProject )
include( install-dependency )

download_project(
  PROJ boost-ios
  GIT_REPOSITORY https://github.com/j-jorge/boost-for-ios.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
  )

execute_process(
  COMMAND ${boost-ios_SOURCE_DIR}/boost.sh
    --with-libraries=filesystem,thread,system
    --arch=${IOS_ARCH}
  WORKING_DIRECTORY ${boost-ios_BINARY_DIR}
)

install_dependency(
  HEADERS "${boost-ios_BINARY_DIR}/ios/prefix/include/"
  LIBRARIES "${boost-ios_BINARY_DIR}/ios/prefix/lib"
  )

set(
  Boost_INCLUDE_DIR
  "${boost-ios_BINARY_DIR}/ios/prefix/include"
  )
set(
  Boost_LIBRARY_DIR
  "${boost-ios_BINARY_DIR}/ios/prefix/lib"
  )

