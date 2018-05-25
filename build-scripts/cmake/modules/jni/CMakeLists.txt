project( iscool-jni )

include( declare-iscool-library )

find_package(
  Boost ${required_boost_version} REQUIRED
  )

declare_iscool_library( NAME jni
  FILES
  "bad_cast.cpp"
  "cast_jint.cpp"
  "cast_std_string.cpp"
  "check_java_exception.cpp"
  "log_context.cpp"
  "new_java_long.cpp"
  "new_java_string.cpp"
  "scoped_native_callback.cpp"
  "setup.cpp"
  "string_bytes.cpp"
  "throw_java_exception.cpp"
  "to_string.cpp"

  "detail/get_class.cpp"
  "detail/get_jni_env.cpp"
  "detail/get_method_info.cpp"
  "detail/get_static_method_info.cpp"
  "detail/method_base.cpp"
  "detail/native_callback.cpp"
  "detail/native_call.cpp"
  "detail/native_call_manager.cpp"
  "detail/static_method_base.cpp"

  LINK
  iscool_log
  iscool_schedule
  iscool_signals
  Boost::boost

  ANDROID
  )
