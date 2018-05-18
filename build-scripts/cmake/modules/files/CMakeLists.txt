project( iscool-files )

include( declare-iscool-library )
include( declare-iscool-library-test )

find_package(
  Boost ${required_boost_version} REQUIRED filesystem system
  )

declare_iscool_library( NAME files
  FILES
  "boost_delegates.cpp"
  "copy_file.cpp"
  "create_directories.cpp"
  "delete_directory.cpp"
  "delete_file.cpp"
  "file_exists.cpp"
  "file_system_delegates.cpp"
  "full_path_exists.cpp"
  "get_full_path.cpp"
  "get_writable_path.cpp"
  "log_context.cpp"
  "read_file.cpp"
  "rename_file.cpp"
  "setup.cpp"
  "detail/system_delegates.cpp"
  
  INCLUDE
  ${Boost_INCLUDE_DIRS}
  
  LINK
  iscool_log
  ${Boost_LIBRARIES}
  )

iscool_module_directory( test_source_root files tests/src )
iscool_module_include_directory( test_include_root files tests )

add_library(
  iscool_files_testing
  ${test_source_root}/test/empty_file_delegates.cpp
  )

target_include_directories(
  iscool_files_testing
  PUBLIC
  ${test_include_root}
  )

target_link_libraries(
  iscool_files_testing
  PUBLIC
  iscool_files
  )

declare_iscool_library_test( NAME files
  FILES
  "file_system_delegates.cpp"
  "setup.cpp"

  LINK
  iscool_files_testing
  )
