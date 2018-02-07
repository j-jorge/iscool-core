if( JSONCPP_INCLUDE_DIR )
  message(
    "Skipping build for JsonCpp library. JSONCPP_INCLUDE_DIR=${JSONCPP_INCLUDE_DIR}"
    )
  return()
endif()

include( DownloadProject )
include( install-dependency )

download_project(
  PROJ jsoncpp
  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
  )

add_subdirectory(
  ${jsoncpp_SOURCE_DIR}
  ${jsoncpp_BINARY_DIR}
  EXCLUDE_FROM_ALL
  )

install_dependency(
  HEADERS "${jsoncpp_SOURCE_DIR}/include/"
  LIBRARIES "${jsoncpp_BINARY_DIR}/src/lib_json"
  EXCLUDE "CMakeLists.txt"
  )

set( JSONCPP_INCLUDE_DIR "${jsoncpp_SOURCE_DIR}/include" )
set( JSONCPP_LIBRARIES "jsoncpp_lib_static" )
