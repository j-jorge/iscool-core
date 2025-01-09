project( iscool-net )

include( declare-iscool-library )
include( declare-iscool-library-test )

find_package(
  Boost ${required_boost_version} REQUIRED COMPONENTS system
  )

declare_iscool_library( NAME net
  FILES
  "byte_array_bit_inserter.cpp"
  "byte_array_bit_reader.cpp"
  "byte_array.cpp"
  "byte_array_from_stream.cpp"
  "byte_array_reader.cpp"
  "decode_base64_string.cpp"
  "encode_base64_string.cpp"
  "endianness.cpp"
  "log_context.cpp"
  "message_channel.cpp"
  "message_deserializer.cpp"
  "message_pool.cpp"
  "message_stream.cpp"
  "socket_stream.cpp"
  "socket_stream_pool.cpp"

  "detail/apply_xor.cpp"
  "detail/base64_chars.cpp"
  "detail/socket.cpp"

  "message/deserialize_message.cpp"
  "message/message.cpp"
  "message/serialize_message.cpp"

  LINK
  Boost::system
  iscool_iterators
  iscool_meta
  iscool_schedule
  iscool_signals
  )

declare_iscool_library_test( NAME net
  FILES
  "byte_array_bit_inserter.cpp"
  "byte_array_bit_reader.cpp"
  "byte_array.cpp"
  "byte_array_from_stream.cpp"
  "byte_array_reader.cpp"
  "byte_array_test_helper.cpp"
  "decode_base64_string.cpp"
  "encode_base64_string.cpp"
  "message_channel.cpp"
  "message_test.cpp"

  "byte_array_serialization/byte_array_array_serialization_test.cpp"
  "byte_array_serialization/byte_array_enum_serialization_test.cpp"
  "byte_array_serialization/byte_array_serialization_test.cpp"
  "byte_array_serialization/byte_array_tuple_serialization_test.cpp"
  "byte_array_serialization/byte_array_vector_serialization_test.cpp"

  "message/raw_message.cpp"
  )
