if( USE_DEFAULT_JSONCPP )
  find_package( jsoncpp REQUIRED )
  return()
endif()

include( DownloadProject )
include( install-dependency )

download_project(
  PROJ jsoncpp
  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
  GIT_TAG 1.9.6
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

add_library( JsonCpp::JsonCpp INTERFACE IMPORTED )
set_target_properties(
  JsonCpp::JsonCpp
  PROPERTIES
  INTERFACE_LINK_LIBRARIES jsoncpp_static
  INTERFACE_INCLUDE_DIRECTORIES ${jsoncpp_SOURCE_DIR}/include
  )
