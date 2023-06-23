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
#include "iscool/net/decode_base64_string.h"

#include "iscool/net/byte_array_reader.h"

#include "iscool/net/detail/base64_chars.h"

namespace iscool
{
  namespace net
  {
    namespace detail
    {
      static bool is_base64(unsigned char c);

      static byte_array
      extract_byte_array(std::array<std::uint8_t, 4> character);
    }
  }
}

iscool::net::byte_array
iscool::net::decode_base64_string(const std::string& string)
{
  iscool::net::byte_array result;

  std::array<std::uint8_t, 4> character;
  auto cursor(character.begin());

  for (auto it(string.begin()); it != string.end() && detail::is_base64(*it);
       ++it)
    {
      (*cursor) = detail::base64_chars.find(*it);
      ++cursor;

      if (cursor != character.end())
        continue;

      result.append(detail::extract_byte_array(character));
      cursor = character.begin();
    }

  if (cursor != character.begin())
    {
      std::fill(cursor, character.end(), 0);

      byte_array to_append = detail::extract_byte_array(character);
      result.append(
          byte_array_reader(to_append).slice(cursor - character.begin() - 1));
    }

  return result;
}

bool iscool::net::detail::is_base64(unsigned char c)
{
  return (std::isalnum(c) || (c == '+') || (c == '/'));
}

iscool::net::byte_array
iscool::net::detail::extract_byte_array(std::array<std::uint8_t, 4> character)
{
  std::array<std::uint8_t, 3> resulting_array;
  resulting_array[0] = (character[0] << 2) | ((character[1] & 0x30) >> 4);
  resulting_array[1] =
      ((character[1] & 0xf) << 4) | ((character[2] & 0x3c) >> 2);
  resulting_array[2] = ((character[2] & 0x3) << 6) | character[3];

  return iscool::net::byte_array(resulting_array.begin(),
                                 resulting_array.end());
}
