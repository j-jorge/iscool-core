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
  typedef typename iscool::meta::underlying_type<T>::type raw_type;

  const raw_type raw_value(
      to_network_endianness(static_cast<const raw_type>(value)));

  const std::uint8_t* p(reinterpret_cast<const std::uint8_t*>(&raw_value));
  _content.insert(_content.end(), p, p + sizeof(T));
}

template <typename Iterator>
void iscool::net::byte_array::append(const Iterator& first,
                                     const Iterator& last)
{
  _content.reserve(_content.size() + last - first);

  for (Iterator it(first); it != last; ++it)
    append(*it);
}
