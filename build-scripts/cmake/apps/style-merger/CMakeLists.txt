include( install )

find_package(
  Boost ${required_boost_version} REQUIRED COMPONENTS program_options
  )

add_executable(
  style-merger
  ${source_root}/apps/style-merger/src/main.cpp
  )

target_link_libraries(
  style-merger
  PRIVATE
  Boost::program_options
  iscool_style
  )

install( TARGETS style-merger RUNTIME DESTINATION ${executable_install_dir} )
