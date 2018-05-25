project( iscool-locale )

include( declare-iscool-library )
include( declare-iscool-library-test )

find_package(
  Boost ${required_boost_version} COMPONENTS locale
  )

if ( Boost_FOUND )
  set( LIBRARIES Boost::locale )
else()
  message(
    WARNING
    "Boost.Locale not found. iscool::locale will fail at run time."
    )
endif()

declare_iscool_library( NAME locale
  FILES
  "character_range.cpp"

  LINK
  ${LIBRARIES}
  )

if ( Boost_FOUND )
  target_compile_definitions( iscool_locale PUBLIC ISCOOL_HAS_BOOST_LOCALE )
endif()

declare_iscool_library_test( NAME locale
  FILES
  "character_range.cpp"
  )
