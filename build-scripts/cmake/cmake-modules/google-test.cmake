if( USE_DEFAULT_GOOGLE_TEST )
  find_path( google_test_INCLUDE_DIRS gtest/gtest.h )
  find_library( google_test_library gtest )
  find_library( google_test_main_library gtest_main )

  set(
    google_test_LIBRARIES
    ${google_test_library}
    ${google_test_main_library}
    pthread
    )

  return()
endif()

include( DownloadProject )

download_project(
  PROJ google-test
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
  UPDATE_DISCONNECTED 1
  )

add_subdirectory(
  ${google-test_SOURCE_DIR}
  ${google-test_BINARY_DIR}
  EXCLUDE_FROM_ALL
  )

set( google_test_INCLUDE_DIRS "${google-test_SOURCE_DIR}/include" )
set( google_test_LIBRARIES gtest gtest_main )
