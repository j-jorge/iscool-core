project( iscool-json )

include( jsoncpp )
include( declare-iscool-library )
include( declare-iscool-library-test )

if( TARGET_ANDROID )
  set( platform_arguments ANDROID )
endif()

declare_iscool_library( NAME json
  FILES
  "bad_cast.cpp"
  "from_file.cpp"
  "is_member.cpp"
  "log_context.cpp"
  "optional.cpp"
  "parse_stream.cpp"
  "parse_string.cpp"
  "write_to_stream.cpp"

  "detail/cast_bool.cpp"
  "detail/cast_float.cpp"
  "detail/cast_int64.cpp"
  "detail/cast_int.cpp"
  "detail/cast_string.cpp"
  "detail/cast_uint64.cpp"
  "detail/cast_uint8.cpp"
  "detail/cast_uint.cpp"

  INCLUDE
  ${jsoncpp_INCLUDE_DIRS}
  
  LINK
  ${jsoncpp_LIBRARIES}
  iscool_files

  ${platform_arguments}
  )

declare_iscool_library_test( NAME json
  FILES
  "cast_array.cpp"
  "cast_bool.cpp"
  "cast_float.cpp"
  "cast_int64.cpp"
  "cast_int.cpp"
  "cast_string.cpp"
  "cast_uint64.cpp"
  "cast_uint8.cpp"
  "cast_uint.cpp"
  "cast_unordered_map.cpp"
  "cast_vector.cpp"
  "collection_cast.cpp"
  "is_member.cpp"
  "parse_stream.cpp"
  "to_array.cpp"
  "write_to_stream.cpp"
  )
