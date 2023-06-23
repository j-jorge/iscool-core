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
#include <iscool/net/byte_array_bit_inserter.hpp>

#include <iscool/net/byte_array.hpp>

#include <limits.h>

static_assert(CHAR_BIT == 8,
              "Only eight bits per byte platforms are supported.");

iscool::net::byte_array_bit_inserter::byte_array_bit_inserter(
    byte_array& array)
  : _array(array)
  , _buffer(0)
  , _available_bits(CHAR_BIT)
{}

iscool::net::byte_array_bit_inserter::~byte_array_bit_inserter()
{
  flush();
}

void iscool::net::byte_array_bit_inserter::flush()
{
  _array.append(_buffer);
  _buffer = 0;
  _available_bits = CHAR_BIT;
}

void iscool::net::byte_array_bit_inserter::append(std::uint8_t value,
                                                  std::uint8_t bit_count)
{
  const std::uint8_t direct_insert(std::min(bit_count, _available_bits));
  const std::uint8_t next_insert(bit_count - direct_insert);

  const std::uint8_t direct_mask(((1 << direct_insert) - 1) << next_insert);

  _buffer |= ((value & direct_mask) >> next_insert)
             << (_available_bits - direct_insert);

  if (next_insert == 0)
    _available_bits -= bit_count;
  else
    {
      flush();

      const std::uint8_t next_mask((1 << next_insert) - 1);

      _buffer = (value & next_mask) << (_available_bits - next_insert);
      _available_bits = CHAR_BIT - next_insert;
    }
}
