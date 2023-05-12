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
#ifndef ISCOOL_META_FUNCTION_FROM_SIGNATURE_H
#define ISCOOL_META_FUNCTION_FROM_SIGNATURE_H

#include <functional>

namespace iscool
{
    namespace meta
    {
        template< typename R, typename... Arg >
        struct function_from_signature
        {
            template< template<class> class Wrapper >
            struct in_functor
            {
                typedef Wrapper< R(Arg...) > type;
            };

            typedef typename in_functor< std::function >::type type;
        };

        template< typename R >
        struct function_from_signature< R, void >
        {
            template< template<class> class Wrapper >
            struct in_functor
            {
                typedef Wrapper< R() > type;
            };

            typedef typename in_functor< std::function >::type type;
        };
    }
}

#endif
