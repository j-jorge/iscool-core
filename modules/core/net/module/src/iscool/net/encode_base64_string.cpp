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
#include <iscool/net/encode_base64_string.hpp>

#include <iscool/net/detail/base64_chars.hpp>

namespace iscool::net::detail
{
  static std::array<std::uint8_t, 4>
  encode_character(const std::array<std::byte, 3>& character);
}

std::string iscool::net::encode_base64_string(std::span<const std::byte> input)
{
  std::string result;

  std::array<std::byte, 3> character;
  const std::array<std::byte, 3>::iterator character_begin(character.begin());
  const std::array<std::byte, 3>::iterator character_end(character.end());
  const std::span<const std::byte>::iterator input_end(input.end());

  auto cursor(character_begin);
  for (auto it(input.begin()); it != input_end; ++it)
    {
      (*cursor) = *it;
      ++cursor;

      if (cursor != character_end)
        continue;

      for (auto c : detail::encode_character(character))
        result += detail::base64_chars[c];
      cursor = character_begin;
    }

  if (cursor != character_begin)
    {
      std::fill(cursor, character_end, std::byte(0));

      const std::array<std::uint8_t, 4> encoded_character(
          detail::encode_character(character));

      const std::size_t remaining_count(cursor - character_begin + 1);
      for (std::size_t i(0); i != remaining_count; ++i)
        result += detail::base64_chars[encoded_character[i]];

      for (; cursor != character_end; ++cursor)
        result += '=';
    }

  return result;
}

std::array<std::uint8_t, 4> iscool::net::detail::encode_character(
    const std::array<std::byte, 3>& character)
{
  std::array<std::uint8_t, 4> resulting_array;
  resulting_array[0] =
      std::to_integer<std::uint8_t>((character[0] & std::byte(0xfc)) >> 2);
  resulting_array[1] =
      std::to_integer<std::uint8_t>(((character[0] & std::byte(0x03)) << 4)
                                    | ((character[1] & std::byte(0xf0)) >> 4));
  resulting_array[2] =
      std::to_integer<std::uint8_t>(((character[1] & std::byte(0x0f)) << 2)
                                    | ((character[2] & std::byte(0xc0)) >> 6));
  resulting_array[3] =
      std::to_integer<std::uint8_t>(character[2] & std::byte(0x3f));

  return resulting_array;
}
