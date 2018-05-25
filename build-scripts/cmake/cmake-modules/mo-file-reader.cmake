if( USE_DEFAULT_MO_FILE_READER )
  find_package( moFileReader )
  return()
endif()

include( DownloadProject )
include( install-dependency )

download_project(
  PROJ mofilereader
  GIT_REPOSITORY https://github.com/IsCoolEntertainment/mofilereader
  GIT_TAG master
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

set_target_properties(
  moFileReader
  PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${mofilereader_SOURCE_DIR}/include"
  )
