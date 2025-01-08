/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
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
