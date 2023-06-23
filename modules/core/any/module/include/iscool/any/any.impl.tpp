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
#ifndef ISCOOL_ANY_ANY_IMPL_TPP
#define ISCOOL_ANY_ANY_IMPL_TPP

#include <iscool/any/detail/get_vtable.hpp>
#include <iscool/any/detail/vtable.hpp>

#include <iscool/memory/global_pool.hpp>
#include <iscool/memory/global_pool.impl.tpp>

template <typename T>
iscool::any::any::any(const T& value)
  : _value(iscool::memory::get_global_pool<T>().construct(value))
  , _vtable(detail::get_vtable<T>())
{}

template <typename T>
const T* iscool::any::any::get() const
{
  return (_vtable->type_id == typeid(T).hash_code())
             ? reinterpret_cast<const T*>(_value)
             : nullptr;
}

template <typename Visitor>
void iscool::any::any::visit(Visitor visitor) const
{
  visitor.visit(_vtable->type_id, _value);
}

#endif
