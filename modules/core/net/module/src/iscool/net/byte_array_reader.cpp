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

#include <iscool/net/byte_array.hpp>

iscool::net::byte_array_reader::byte_array_reader(byte_array byte_array)
  : _byte_array(std::move(byte_array))
  , _current_index(0)
{}

iscool::net::byte_array
iscool::net::byte_array_reader::get_raw(std::size_t size)
{
  const byte_array result(slice(size));
  _current_index += size;
  return result;
}

iscool::net::byte_array iscool::net::byte_array_reader::slice() const
{
  return slice(_byte_array.size() - _current_index);
}

iscool::net::byte_array
iscool::net::byte_array_reader::slice(std::size_t size) const
{
  const byte_array::const_iterator first(_byte_array.begin() + _current_index);
  return byte_array(first, first + size);
}

bool iscool::net::byte_array_reader::has_next() const
{
  return _current_index != _byte_array.size();
}
