project( iscool-factory )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME
  factory

  LINK
  iscool_log
  iscool_strings

  TEST
  "dynamic_factory.cpp"
  "dynamic_factory_registrar.cpp"

  TEST_LINK
  iscool_testing
)
