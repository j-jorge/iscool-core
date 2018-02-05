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
#ifndef ISCOOL_NET_ENDIANNESS_TPP
#define ISCOOL_NET_ENDIANNESS_TPP

#include <algorithm>

template<typename T, std::size_t S>
std::array<T, S> iscool::net::to_network_endianness( std::array<T, S> value )
{
    typedef typename std::array<T, S>::iterator iterator;
    std::transform<iterator, iterator, T(*)(T)>
        ( value.begin(), value.end(), value.begin(), to_network_endianness );
    return value;
}

template<typename T, std::size_t S>
std::array<T, S> iscool::net::to_host_endianness( std::array<T, S> value )
{
    typedef typename std::array<T, S>::iterator iterator;
    std::transform<iterator, iterator, T(*)(T)>
        ( value.begin(), value.end(), value.begin(), to_host_endianness );
    return value;
}


#endif
