include(CMakePackageConfigHelpers)

install(
  EXPORT iscool-core
  DESTINATION lib/cmake/iscool-core/
  FILE iscool-core-config-generated.cmake
  )

configure_file(
  iscool-core-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/iscool-core-config.cmake
  @ONLY
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/iscool-core-config-version.cmake
  COMPATIBILITY SameMinorVersion
  )

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/iscool-core-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/iscool-core-config-version.cmake
  DESTINATION lib/cmake/iscool-core/
  )
