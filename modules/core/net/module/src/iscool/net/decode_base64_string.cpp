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
#include <iscool/net/decode_base64_string.hpp>

#include <iscool/net/byte_array_reader.hpp>

#include <iscool/net/detail/base64_chars.hpp>

namespace iscool::net::detail
{
  static bool is_base64(char c);
  static std::array<std::byte, 3>
  extract_bytes(const std::array<std::byte, 4>& character);
}

std::size_t
iscool::net::size_of_decoded_base64_string(const std::string& string)
{
  const std::size_t n = string.size();

  std::size_t r = 3 * n / 4;
  r -= (n >= 1) && (string[n - 1] == '=');
  r -= (n >= 2) && (string[n - 2] == '=');

  return r;
}

void iscool::net::decode_base64_string(std::span<std::byte> output,
                                       const std::string& string)
{
  std::span<std::byte>::iterator out = output.begin();
  std::array<std::byte, 4> character;
  auto cursor(character.begin());

  for (auto it = string.begin(), eit = string.end();
       (it != eit) && detail::is_base64(*it); ++it)
    {
      (*cursor) = std::byte(detail::base64_chars.find(*it));
      ++cursor;

      if (cursor != character.end())
        continue;

      for (std::byte b : detail::extract_bytes(character))
        {
          *out = b;
          ++out;
        }

      cursor = character.begin();
    }

  if (cursor != character.begin())
    {
      std::fill(cursor, character.end(), std::byte(0));

      const std::array<std::byte, 3> bytes = detail::extract_bytes(character);
      std::copy_n(bytes.begin(), cursor - character.begin() - 1, out);
    }
}

bool iscool::net::detail::is_base64(char c)
{
  return (std::isalnum(c) || (c == '+') || (c == '/'));
}

std::array<std::byte, 3>
iscool::net::detail::extract_bytes(const std::array<std::byte, 4>& character)
{
  std::array<std::byte, 3> result;
  result[0] = (character[0] << 2) | ((character[1] & std::byte(0x30)) >> 4);
  result[1] = ((character[1] & std::byte(0xf)) << 4)
              | ((character[2] & std::byte(0x3c)) >> 2);
  result[2] = ((character[2] & std::byte(0x3)) << 6) | character[3];

  return result;
}
