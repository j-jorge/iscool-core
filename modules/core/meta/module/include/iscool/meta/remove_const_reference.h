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
#ifndef ISCOOL_META_REMOVE_CONST_REFERENCE_H
#define ISCOOL_META_REMOVE_CONST_REFERENCE_H

namespace iscool
{
    namespace meta
    {
        template< typename T >
        struct remove_const_reference;

        template< typename T >
        struct remove_const_reference< T& >
        {
            typedef typename remove_const_reference< T >::type type;
        };

        template< typename T >
        struct remove_const_reference< const T >
        {
            typedef typename remove_const_reference< T >::type type;
        };

        template< typename T >
        struct remove_const_reference
        {
            typedef T type;
        };
    }
}

#include "iscool/meta/detail/remove_const_reference.tests.h"

#endif
