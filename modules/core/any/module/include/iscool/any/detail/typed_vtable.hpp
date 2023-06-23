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
#ifndef ISCOOL_ANY_DETAIL_TYPED_VTABLE_H
#define ISCOOL_ANY_DETAIL_TYPED_VTABLE_H

namespace iscool
{
  namespace any
  {
    class any;

    namespace detail
    {
      template <typename T>
      class typed_vtable
      {
      public:
        static void clear(any& that);
        static void copy(any& target, const any& source);
        static void move(any& target, any&& source);
      };

      template <>
      class typed_vtable<void>
      {
      public:
        static void clear(any& that);
        static void copy(any& target, const any& source);
        static void move(any& target, any&& source);
      };
    }
  }
}

#include <iscool/any/detail/typed_vtable.tpp>

#endif
