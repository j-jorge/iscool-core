install(
  EXPORT iscool-core
  DESTINATION lib/cmake/iscool-core/
  FILE iscool-core-config-generated.cmake
  )

configure_file(
  iscool-core-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/iscool-core-config.cmake
  @ONLY )

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/iscool-core-config.cmake
  DESTINATION lib/cmake/iscool-core/
  )
