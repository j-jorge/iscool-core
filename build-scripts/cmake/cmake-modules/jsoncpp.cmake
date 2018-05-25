if( USE_DEFAULT_JSONCPP )
  find_package( jsoncpp )
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

add_library( jsoncpp INTERFACE IMPORTED )
set_target_properties(
  jsoncpp
  PROPERTIES
  INTERFACE_LINK_LIBRARIES "jsoncpp_lib_static"
  INTERFACE_INCLUDE_DIRECTORIES ${jsoncpp_SOURCE_DIR}/include
  )
