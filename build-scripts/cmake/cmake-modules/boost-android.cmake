project( boost-android NONE )

include( DownloadProject )
include( install-dependency )

download_project(
  PROJ boost-android
  GIT_REPOSITORY https://github.com/j-jorge/Boost-for-Android.git
  GIT_TAG "1.58.0-10e"
  UPDATE_DISCONNECTED 1
  )

execute_process(
  COMMAND ${boost-android_SOURCE_DIR}/build-android.sh
    --with-libraries=system
    --abi=${CMAKE_ANDROID_ARCH_ABI}
    --boost=${required_boost_version}
    ${CMAKE_ANDROID_NDK}
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
