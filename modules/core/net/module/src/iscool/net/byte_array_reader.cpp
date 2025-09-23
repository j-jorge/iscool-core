// SPDX-License-Identifier: Apache-2.0
#include <iscool/net/byte_array_reader.hpp>

#include <stdexcept>

iscool::net::byte_array_reader::byte_array_reader(
    std::span<const std::uint8_t> bytes)
  : _bytes(bytes)
  , _current_index(0)
{}

std::span<const std::uint8_t> iscool::net::byte_array_reader::raw()
{
  return raw(remaining_bytes());
}

std::span<const std::uint8_t>
iscool::net::byte_array_reader::raw(std::size_t size)
{
  if (size > remaining_bytes())
    throw std::out_of_range("not enough bytes.");

  const std::span<const std::uint8_t> result(
      _bytes.subspan(_current_index, size));
  _current_index += size;
  return result;
}

bool iscool::net::byte_array_reader::has_next() const
{
  return _current_index != _bytes.size();
}

std::size_t iscool::net::byte_array_reader::remaining_bytes() const
{
  return _bytes.size() - _current_index;
}
