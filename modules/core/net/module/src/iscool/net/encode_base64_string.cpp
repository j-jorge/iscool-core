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
#include "iscool/net/encode_base64_string.h"

#include "iscool/net/detail/base64_chars.h"

namespace iscool
{
  namespace net
  {
    namespace detail
    {
      static std::array<std::uint8_t, 4>
      encode_character(const std::array<std::uint8_t, 3>& character);
    }
  }
}

std::string iscool::net::encode_base64_string(const byte_array& input)
{
  std::vector<char> result;

  std::array<std::uint8_t, 3> character;
  const std::array<std::uint8_t, 3>::iterator character_begin(
      character.begin());
  const std::array<std::uint8_t, 3>::iterator character_end(character.end());
  const byte_array::const_iterator input_end(input.end());

  auto cursor(character_begin);
  for (auto it(input.begin()); it != input_end; ++it)
    {
      (*cursor) = *it;
      ++cursor;

      if (cursor != character_end)
        continue;

      for (auto c : detail::encode_character(character))
        result.emplace_back(detail::base64_chars[c]);
      cursor = character_begin;
    }

  if (cursor != character_begin)
    {
      std::fill(cursor, character_end, '\0');

      const std::array<std::uint8_t, 4> encoded_character(
          detail::encode_character(character));

      const std::size_t remaining_count(cursor - character_begin + 1);
      for (std::size_t i(0); i != remaining_count; ++i)
        result.emplace_back(detail::base64_chars[encoded_character[i]]);

      for (; cursor != character_end; ++cursor)
        result.emplace_back('=');
    }

  return std::string(result.begin(), result.end());
}

std::array<std::uint8_t, 4> iscool::net::detail::encode_character(
    const std::array<std::uint8_t, 3>& character)
{
  std::array<std::uint8_t, 4> resulting_array;
  resulting_array[0] = (character[0] & 0xfc) >> 2;
  resulting_array[1] =
      ((character[0] & 0x03) << 4) | ((character[1] & 0xf0) >> 4);
  resulting_array[2] =
      ((character[1] & 0x0f) << 2) | ((character[2] & 0xc0) >> 6);
  resulting_array[3] = character[2] & 0x3f;

  return resulting_array;
}
