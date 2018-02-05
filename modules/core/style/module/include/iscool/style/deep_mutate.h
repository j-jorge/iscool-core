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
#ifndef ISCOOL_STYLE_DEEP_MUTATE_H
#define ISCOOL_STYLE_DEEP_MUTATE_H

#include <array>

namespace iscool
{
    namespace style
    {
        class declaration;
        
        template< typename Mutation, std::size_t N >
        void deep_mutate
        ( declaration& style, const std::array< std::string, N >& path,
          Mutation mutation );
    }
}

#include "iscool/style/detail/deep_mutate.tpp"

#endif
