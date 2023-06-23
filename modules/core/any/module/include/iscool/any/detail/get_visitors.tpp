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
#ifndef ISCOOL_ANY_DETAIL_GET_VISITORS_TPP
#define ISCOOL_ANY_DETAIL_GET_VISITORS_TPP

#include <cassert>
#include <typeinfo>

namespace iscool
{
  namespace any
  {
    namespace detail
    {
      template <typename T, typename Visitor>
      void visit(void* value, Visitor visitor);

      template <typename Visitor, typename T>
      struct visitor_map_entry_builder
      {
        static std::pair<std::size_t, void (*)(void*, Visitor)> build();
      };

      template <typename Visitor, typename Types>
      class visitor_map_builder;

      template <typename Visitor, typename... T>
      class visitor_map_builder<Visitor, std::tuple<T...>>
      {
      public:
        static const std::unordered_map<std::size_t, void (*)(void*, Visitor)>&
        get();
      };
    }
  }
}

template <typename Visitor, typename Types>
const std::unordered_map<std::size_t, void (*)(void*, Visitor)>&
iscool::any::detail::get_visitors()
{
  return visitor_map_builder<Visitor, Types>::get();
}

template <typename Visitor, typename... T>
const std::unordered_map<std::size_t, void (*)(void*, Visitor)>&
iscool::any::detail::visitor_map_builder<Visitor, std::tuple<T...>>::get()
{
  static std::unordered_map<std::size_t, void (*)(void*, Visitor)> result(
      { visitor_map_entry_builder<Visitor, T>::build()... });

  return result;
}

template <typename Visitor, typename T>
std::pair<std::size_t, void (*)(void*, Visitor)>
iscool::any::detail::visitor_map_entry_builder<Visitor, T>::build()
{
  return { typeid(T).hash_code(), &visit<T, Visitor> };
}

template <typename T, typename Visitor>
void iscool::any::detail::visit(void* value, Visitor visitor)
{
  assert(value != nullptr);
  visitor(*reinterpret_cast<const T*>(value));
}

#endif
