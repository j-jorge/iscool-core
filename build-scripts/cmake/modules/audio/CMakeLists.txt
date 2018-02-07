project( iscool-audio )

include( declare-iscool-library )
include( declare-iscool-library-test )

declare_iscool_library( NAME audio
  FILES
  "default_effect_player.cpp"
  "default_mixer.cpp"
  "mixer.cpp"

  "detail/default_mixer.cpp"

  LINK
  iscool_resources
  )

declare_iscool_library_test( NAME audio
  FILES
  "default_effect_player.cpp"
  "mixer.cpp"

  "test/platform_mixer_mockup.cpp"

  LINK
  iscool_files_testing
  )
