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
#ifndef ISCOOL_NET_BYTE_ARRAY_SERIALIZATION_H
#define ISCOOL_NET_BYTE_ARRAY_SERIALIZATION_H

namespace iscool
{
    namespace net
    {
        class byte_array;
        class byte_array_reader;

        template<typename T>
        byte_array& operator<<( byte_array& output, const T& value );
        
        template<typename T>
        byte_array_reader& operator>>( byte_array_reader& input, T& value );
    }
}

#include "iscool/net/byte_array_serialization/byte_array_serialization.tpp"

#endif
