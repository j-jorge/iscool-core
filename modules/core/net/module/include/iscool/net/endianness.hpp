// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <array>
#include <cstdint>

namespace iscool::net
{
  bool to_host_endianness(bool value);
  std::uint8_t to_host_endianness(std::uint8_t value);
  std::uint16_t to_host_endianness(std::uint16_t value);
  std::uint32_t to_host_endianness(std::uint32_t value);
  std::uint64_t to_host_endianness(std::uint64_t value);

  template <typename T, std::size_t S>
  std::array<T, S> to_host_endianness(std::array<T, S> value);

  bool to_network_endianness(bool value);
  std::uint8_t to_network_endianness(std::uint8_t value);
  std::uint16_t to_network_endianness(std::uint16_t value);
  std::uint32_t to_network_endianness(std::uint32_t value);
  std::uint64_t to_network_endianness(std::uint64_t value);

  template <typename T, std::size_t S>
  std::array<T, S> to_network_endianness(std::array<T, S> value);
}

#include <iscool/net/endianness.tpp>
