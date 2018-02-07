project( iscool-any )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME any
  FILES
  "any.cpp"
  "detail/typed_vtable.cpp"
  LINK
  iscool_memory
  )

declare_iscool_library_test( NAME any
  FILES
  "any.cpp"
  )
