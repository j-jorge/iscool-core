// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstdint>
#include <span>

namespace iscool::net
{
  class byte_array_reader
  {
  public:
    explicit byte_array_reader(std::span<const std::uint8_t> bytes);

    template <typename T>
    T get();

    std::span<const std::uint8_t> raw();
    std::span<const std::uint8_t> raw(std::size_t size);

    bool has_next() const;
    std::size_t remaining_bytes() const;

  private:
    std::span<const std::uint8_t> _bytes;
    std::size_t _current_index;
  };
}

#include <iscool/net/byte_array_reader.tpp>
