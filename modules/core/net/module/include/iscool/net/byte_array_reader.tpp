// SPDX-License-Identifier: Apache-2.0
#include <stdexcept>

#include <iscool/net/endianness.hpp>

#include <iscool/meta/underlying_type.hpp>

#include <algorithm>

template <typename T>
T iscool::net::byte_array_reader::get()
{
  if (_current_index + sizeof(T) > _bytes.size())
    throw std::out_of_range("can't read value out of remaining bytes.");

  using raw_type = typename iscool::meta::underlying_type<T>::type;

  const std::uint8_t* const begin(&_bytes[_current_index]);
  const std::uint8_t* const end(begin + sizeof(T));

  raw_type result;
  std::uint8_t* out(reinterpret_cast<std::uint8_t*>(&result));

  std::copy(begin, end, out);

  _current_index += sizeof(T);

  return static_cast<T>(to_host_endianness(result));
}
