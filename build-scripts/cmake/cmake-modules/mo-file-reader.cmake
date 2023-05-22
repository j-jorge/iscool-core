if( USE_DEFAULT_MO_FILE_READER )
  find_package( moFileReader )
  return()
endif()

include( DownloadProject )
include( install-dependency )

download_project(
  PROJ mofilereader
  GIT_REPOSITORY https://github.com/j-jorge/mofilereader
  GIT_TAG v1.1
  UPDATE_DISCONNECTED 1
  )

add_subdirectory(
  ${mofilereader_SOURCE_DIR}/build
  ${mofilereader_BINARY_DIR}
  EXCLUDE_FROM_ALL
  )

install_dependency(
  HEADERS "${mofilereader_SOURCE_DIR}/include/"
  LIBRARIES "${mofilereader_BINARY_DIR}"
  )
