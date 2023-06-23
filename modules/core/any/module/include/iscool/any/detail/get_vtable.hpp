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
#ifndef ISCOOL_ANY_DETAIL_GET_VTABLE_H
#define ISCOOL_ANY_DETAIL_GET_VTABLE_H

namespace iscool
{
  namespace any
  {
    namespace detail
    {
      class vtable;

      template <typename T>
      vtable* get_vtable();
    }
  }
}

#include <iscool/any/detail/get_vtable.tpp>

#endif