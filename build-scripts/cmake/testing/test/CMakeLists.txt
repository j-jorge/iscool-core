project( iscool-testing )

include( install )

add_library( iscool_testing INTERFACE )

set( lib_include "${source_root}/modules/testing/test/module/include" )

target_include_directories(
  iscool_testing
  INTERFACE
  ${lib_include}
  )

install( DIRECTORY ${lib_include}/iscool DESTINATION ${header_install_dir} )
