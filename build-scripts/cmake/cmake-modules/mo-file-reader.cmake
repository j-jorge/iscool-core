if( MO_FILE_READER_INCLUDE_DIR )
  message(
    "Skipping build for MoFileReader library. MO_FILE_READER_INCLUDE_DIR=${MO_FILE_READER_INCLUDE_DIR}"
    )
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

set( MO_FILE_READER_INCLUDE_DIR "${mofilereader_SOURCE_DIR}/include" )
set( MO_FILE_READER_LIBRARIES "moFileReader.static" )
