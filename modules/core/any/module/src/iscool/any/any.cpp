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
#include <iscool/any/any.hpp>

#include <iscool/any/detail/get_vtable.hpp>
#include <iscool/any/detail/vtable.hpp>

iscool::any::any::any()
  : _value(nullptr)
  , _vtable(detail::get_vtable<void>())
{}

iscool::any::any::~any()
{
  (*_vtable->clear)(*this);
}

iscool::any::any::any(const any& that)
{
  (*that._vtable->copy)(*this, that);
}

iscool::any::any::any(any&& that)
{
  const detail::vtable* vtable(that._vtable);
  (*vtable->move)(*this, std::move(that));
}

iscool::any::any& iscool::any::any::operator=(const any& that)
{
  if (this == &that)
    return *this;

  (_vtable->clear)(*this);
  (*that._vtable->copy)(*this, that);

  return *this;
}

iscool::any::any& iscool::any::any::operator=(any&& that)
{
  if (this == &that)
    return *this;

  (*_vtable->clear)(*this);

  const detail::vtable* vtable(that._vtable);
  (*vtable->move)(*this, std::move(that));

  return *this;
}
