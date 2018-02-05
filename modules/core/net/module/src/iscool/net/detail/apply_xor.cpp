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
#include "iscool/net/detail/apply_xor.h"

#include "iscool/net/byte_array.h"

#include "iscool/iterators/cycle_iterator.h"
#include "iscool/iterators/cycle_iterator.impl.tpp"

#include <algorithm>
#include <functional>

void iscool::net::detail::apply_xor( byte_array& bytes, const xor_key& key )
{
    std::transform
        ( bytes.begin(), bytes.end(),
          iterators::cycle_iterator< xor_key::const_iterator >
          ( key.begin(), key.end() ),
          bytes.begin(), std::bit_xor< xor_key::value_type >() );
}
