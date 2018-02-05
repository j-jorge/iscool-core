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
#ifndef ISCOOL_NET_ENDIANNESS_H
#define ISCOOL_NET_ENDIANNESS_H

#include <cstdint>
#include <array>

namespace iscool
{
    namespace net
    {
        std::uint8_t to_host_endianness( std::uint8_t value );
        std::uint16_t to_host_endianness( std::uint16_t value );
        std::uint32_t to_host_endianness( std::uint32_t value );
        std::uint64_t to_host_endianness( std::uint64_t value );

        template<typename T, std::size_t S>
        std::array<T, S> to_host_endianness( std::array<T, S> value );

        std::uint8_t to_network_endianness( std::uint8_t value );
        std::uint16_t to_network_endianness( std::uint16_t value );
        std::uint32_t to_network_endianness( std::uint32_t value );
        std::uint64_t to_network_endianness( std::uint64_t value );

        template<typename T, std::size_t S>
        std::array<T, S> to_network_endianness( std::array<T, S> value );
    }
}

#include "iscool/net/endianness.tpp"

#endif
