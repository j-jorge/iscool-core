project( iscool-files )

include( declare-iscool-library )
include( declare-iscool-library-test )
include( install )

find_package(
  Boost ${required_boost_version} REQUIRED system
  )

declare_iscool_library( NAME files
  FILES
  "copy_file.cpp"
  "create_parent_directories.cpp"
  "default_file_system_delegates.cpp"
  "delete_directory.cpp"
  "delete_file.cpp"
  "file_exists.cpp"
  "full_path_exists.cpp"
  "get_full_path.cpp"
  "get_writable_path.cpp"
  "log_context.cpp"
  "read_file.cpp"
  "rename_file.cpp"
  "setup.cpp"
  "detail/system_delegates.cpp"

  LINK
  iscool_log
  Boost::system
  )

iscool_module_directory( test_source_root files tests/src )
iscool_module_include_directory( test_include_root files tests )

add_library(
  iscool_files_testing
  ${test_source_root}/test/file_system_delegates_mockup.cpp
  )

target_include_directories(
  iscool_files_testing
  PUBLIC
  $<BUILD_INTERFACE:${test_include_root}>
  )

target_link_libraries(
  iscool_files_testing
  PUBLIC
  iscool_files
  )

install(
  DIRECTORY ${test_include_root}/iscool
  DESTINATION ${header_install_dir}
  )

install(
  TARGETS iscool_files_testing
  DESTINATION ${library_install_dir}
  ${iscool_core_export}
  )

declare_iscool_library_test( NAME files
  FILES
  "setup.cpp"

  LINK
  iscool_files_testing
  )
