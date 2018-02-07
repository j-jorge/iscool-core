include( DownloadProject )

download_project(
  PROJ google-test
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
  )

add_subdirectory(
  ${google-test_SOURCE_DIR}
  ${google-test_BINARY_DIR}
  EXCLUDE_FROM_ALL
  )
