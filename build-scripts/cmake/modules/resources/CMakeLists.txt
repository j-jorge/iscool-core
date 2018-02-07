project( iscool-resources )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME resources
  FILES
  "catalog.cpp"
  "resolver.cpp"
  "detail/check_extension.cpp"
  "json/to_catalog.cpp"
  
  LINK
  iscool_collections
  iscool_files
  iscool_json
  )

declare_iscool_library_test( NAME resources
  FILES
  "catalog.cpp"
  "resolver.cpp"
  "json/to_catalog.cpp"

  LINK
  iscool_files_testing
  iscool_testing
  )
