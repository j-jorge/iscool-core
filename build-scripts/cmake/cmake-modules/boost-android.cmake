if( Boost_INCLUDE_DIR )
  message(
    "Skipping build for Boost library. Boost_INCLUDE_DIR=${Boost_INCLUDE_DIR}"
    )
  return()
endif()

project( boost-android NONE )

include( DownloadProject )
include( install-dependency )

download_project(
  PROJ boost-android
  GIT_REPOSITORY https://github.com/j-jorge/Boost-for-Android.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
  )

execute_process(
  COMMAND ${boost-android_SOURCE_DIR}/build-android.sh
    --with-libraries=filesystem,thread,system,atomic
    --abi=${CMAKE_ANDROID_ARCH_ABI}
    --boost=${required_boost_version}
  WORKING_DIRECTORY ${boost-android_BINARY_DIR}
)

install_dependency(
  HEADERS "${boost-android_BINARY_DIR}/build-${CMAKE_ANDROID_ARCH_ABI}/include/"
  LIBRARIES "${boost-android_BINARY_DIR}/build-${CMAKE_ANDROID_ARCH_ABI}/lib/"
  )

set(
  Boost_INCLUDE_DIR
  "${boost-android_BINARY_DIR}/build-${CMAKE_ANDROID_ARCH_ABI}/include"
  )
