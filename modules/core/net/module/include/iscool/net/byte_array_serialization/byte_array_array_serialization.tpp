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
#include <iscool/net/byte_array_serialization/byte_array_serialization.hpp>

template <typename T, size_t N>
iscool::net::byte_array& iscool::net::operator<<(byte_array& output,
                                                 const std::array<T, N>& value)
{
  for (const T& item : value)
    output << item;

  return output;
}

template <typename T, size_t N>
iscool::net::byte_array_reader&
iscool::net::operator>>(byte_array_reader& input, std::array<T, N>& value)
{
  for (T& item : value)
    input >> item;

  return input;
}
