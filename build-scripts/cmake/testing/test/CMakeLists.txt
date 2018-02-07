project( iscool-testing )

add_library( iscool_testing INTERFACE )

target_include_directories(
  iscool_testing
  INTERFACE
  "${source_root}/modules/testing/test/module/include"
  )
