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
#include <iscool/net/endianness.hpp>

#include <iscool/meta/underlying_type.hpp>

template <typename Iterator>
iscool::net::byte_array::byte_array(const Iterator& first,
                                    const Iterator& last)
{
  append(first, last);
}

template <typename T>
void iscool::net::byte_array::append(T value)
{
  append(&value, &value + 1);
}

template <typename Iterator>
void iscool::net::byte_array::append(const Iterator& first,
                                     const Iterator& last)
{
  using value_type = std::iterator_traits<Iterator>::value_type;

  std::size_t i = _content.size();
  _content.resize(_content.size() + (last - first) * sizeof(value_type));

  for (Iterator it(first); it != last; ++it, i += sizeof(value_type))
    {
      using raw_type =
          typename iscool::meta::underlying_type<value_type>::type;

      const raw_type raw_value(
          to_network_endianness(static_cast<const raw_type>(*it)));
      const uint8_t* const p =
          reinterpret_cast<const std::uint8_t*>(&raw_value);

      std::copy_n(p, sizeof(value_type), _content.begin() + i);
    }
}
