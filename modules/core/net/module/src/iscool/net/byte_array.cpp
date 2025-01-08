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
#include <iscool/net/byte_array.hpp>

std::span<std::uint8_t> iscool::net::byte_array::span()
{
  return std::span(_content.data(), _content.size());
}

std::span<const std::uint8_t> iscool::net::byte_array::span() const
{
  return std::span(_content.data(), _content.size());
}

void iscool::net::byte_array::append(const byte_array& array)
{
  _content.insert(_content.end(), array.begin(), array.end());
}

std::uint8_t& iscool::net::byte_array::operator[](std::size_t index)
{
  return _content[index];
}

const std::uint8_t&
iscool::net::byte_array::operator[](std::size_t index) const
{
  return _content[index];
}

iscool::net::byte_array::iterator iscool::net::byte_array::begin()
{
  return _content.begin();
}

iscool::net::byte_array::iterator iscool::net::byte_array::end()
{
  return _content.end();
}

iscool::net::byte_array::const_iterator iscool::net::byte_array::begin() const
{
  return _content.begin();
}

iscool::net::byte_array::const_iterator iscool::net::byte_array::end() const
{
  return _content.end();
}

std::uint8_t* iscool::net::byte_array::data()
{
  return _content.data();
}

void iscool::net::byte_array::reserve(std::size_t size)
{
  _content.reserve(size);
}

void iscool::net::byte_array::resize(std::size_t size)
{
  _content.resize(size);
}

std::size_t iscool::net::byte_array::size() const
{
  return _content.size();
}

void iscool::net::byte_array::clear()
{
  return _content.clear();
}

void iscool::net::byte_array::swap(byte_array& that)
{
  _content.swap(that._content);
}
