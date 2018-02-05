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
#ifndef ISCOOL_META_MAKE_INDICES_H
#define ISCOOL_META_MAKE_INDICES_H

#include "iscool/meta/indices.h"

namespace iscool
{
    namespace meta
    {
        template< std::size_t R, std::size_t... I >
        struct make_indices;

        template< std::size_t... I >
        struct make_indices< 0, I... >
        {
            typedef indices< I... > type;
        };

        template< std::size_t R, std::size_t... I >
        struct make_indices
        {
            typedef typename make_indices< R - 1, R - 1, I... >::type type;
        };
    }
}

#endif
