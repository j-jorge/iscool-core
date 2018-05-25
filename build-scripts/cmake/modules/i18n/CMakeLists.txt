project( iscool-i18n )

include( declare-iscool-library )
include( declare-iscool-library-test )
include( mo-file-reader )

declare_iscool_library( NAME i18n
  FILES
  "compact_number_string.cpp"
  "english_numeric_punctuation.cpp"
  "load_translations.cpp"

  "detail/assign_plural_index.cpp"
  "detail/localize.cpp"
  "detail/plural_index.cpp"

  LINK
  moFileReader
  iscool_files
  iscool_strings
  iscool_time
  )

declare_iscool_library_test( NAME i18n
  FILES
  "compact_number_string.cpp"
  "load_translations.cpp"
  "numeric.cpp"
  "relative_past_duration.cpp"

  LINK
  iscool_files_testing
  )

if( TARGET iscool_i18n_test )

  include( build-gettext-translations )

  iscool_module_directory( test_resources i18n tests/resources )
  prepend_string(
    test_resources_files "${test_resources}/"
    de.po
    en.po
    es.po
    fr.po
    it.po
    ja.po
    ko.po
    pt_BR.po
    pt.po
    th.po
    zh_CN.po
    zh_TW.po
    )

  build_gettext_translations(
    TARGET iscool_i18n_test
    FILES ${test_resources_files}
    OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/translations
    )
endif()
