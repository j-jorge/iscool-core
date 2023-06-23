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
#include "iscool/net/endianness.h"

#ifdef __APPLE__

  #include <libkern/OSByteOrder.h>

  #define htobe16(x) OSSwapHostToBigInt16(x)
  #define htole16(x) OSSwapHostToLittleInt16(x)
  #define be16toh(x) OSSwapBigToHostInt16(x)
  #define le16toh(x) OSSwapLittleToHostInt16(x)

  #define htobe32(x) OSSwapHostToBigInt32(x)
  #define htole32(x) OSSwapHostToLittleInt32(x)
  #define be32toh(x) OSSwapBigToHostInt32(x)
  #define le32toh(x) OSSwapLittleToHostInt32(x)

  #define htobe64(x) OSSwapHostToBigInt64(x)
  #define htole64(x) OSSwapHostToLittleInt64(x)
  #define be64toh(x) OSSwapBigToHostInt64(x)
  #define le64toh(x) OSSwapLittleToHostInt64(x)

#else
  #include <endian.h>

  #ifndef be16toh
    #define be16toh(x) betoh16(x)
    #define be32toh(x) betoh32(x)
    #define be64toh(x) betoh64(x)
  #endif
#endif

std::uint8_t iscool::net::to_host_endianness(std::uint8_t value)
{
  return value;
}

std::uint16_t iscool::net::to_host_endianness(std::uint16_t value)
{
  return be16toh(value);
}

std::uint32_t iscool::net::to_host_endianness(std::uint32_t value)
{
  return be32toh(value);
}

std::uint64_t iscool::net::to_host_endianness(std::uint64_t value)
{
  return be64toh(value);
}

std::uint8_t iscool::net::to_network_endianness(std::uint8_t value)
{
  return value;
}

std::uint16_t iscool::net::to_network_endianness(std::uint16_t value)
{
  return htobe16(value);
}

std::uint32_t iscool::net::to_network_endianness(std::uint32_t value)
{
  return htobe32(value);
}

std::uint64_t iscool::net::to_network_endianness(std::uint64_t value)
{
  return htobe64(value);
}
