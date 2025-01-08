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
#include <iscool/net/byte_array_reader.hpp>

iscool::net::byte_array_reader::byte_array_reader(
    std::span<const std::uint8_t> bytes)
  : _bytes(bytes)
  , _current_index(0)
{}

std::span<const std::uint8_t>
iscool::net::byte_array_reader::get_raw(std::size_t size)
{
  const std::span<const std::uint8_t> result(slice(size));
  _current_index += size;
  return result;
}

std::span<const std::uint8_t> iscool::net::byte_array_reader::slice() const
{
  return slice(_bytes.size() - _current_index);
}

std::span<const std::uint8_t>
iscool::net::byte_array_reader::slice(std::size_t size) const
{
  return _bytes.subspan(_current_index, size);
}

bool iscool::net::byte_array_reader::has_next() const
{
  return _current_index != _bytes.size();
}
