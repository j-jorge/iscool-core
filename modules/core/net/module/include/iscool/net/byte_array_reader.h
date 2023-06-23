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
#ifndef ISCOOL_NET_BYTE_ARRAY_READER_H
#define ISCOOL_NET_BYTE_ARRAY_READER_H

#include "iscool/net/byte_array.h"

namespace iscool
{
  namespace net
  {
    class byte_array_reader
    {
    public:
      explicit byte_array_reader(byte_array byte_array);

      template <typename t>
      t get();

      byte_array get_raw(std::size_t size);

      byte_array slice() const;
      byte_array slice(std::size_t size) const;

      bool has_next() const;

    private:
      byte_array _byte_array;
      std::size_t _current_index;
    };
  }
}

#include "iscool/net/byte_array_reader.tpp"

#endif
