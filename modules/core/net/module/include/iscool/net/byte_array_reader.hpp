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
#pragma once

#include <cstdint>
#include <span>

namespace iscool
{
  namespace net
  {
    class byte_array_reader
    {
    public:
      explicit byte_array_reader(std::span<const std::uint8_t> bytes);

      template <typename T>
      T get();

      std::span<const std::uint8_t> get_raw(std::size_t size);

      std::span<const std::uint8_t> slice() const;
      std::span<const std::uint8_t> slice(std::size_t size) const;

      bool has_next() const;

    private:
      std::span<const std::uint8_t> _bytes;
      std::size_t _current_index;
    };
  }
}

#include <iscool/net/byte_array_reader.tpp>
