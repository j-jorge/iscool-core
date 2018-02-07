project( iscool-factory )

include( declare-iscool-library )

declare_iscool_interface_library(
  NAME
  factory

  LINK
  iscool_log
  
  TEST
  "dynamic_factory.cpp"
  "dynamic_factory_registrar.cpp"

  TEST_LINK
  iscool_testing
)
