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
#include "iscool/style/detail/declaration_ref.h"

#include "iscool/style/declaration.h"

iscool::style::detail::declaration_ref::declaration_ref()
{
  new (&_storage) iscool::style::declaration();
}

iscool::style::detail::declaration_ref::declaration_ref(
    const declaration_ref& that)
{
  new (&_storage) iscool::style::declaration(*that);
}

iscool::style::detail::declaration_ref::declaration_ref(declaration_ref&& that)
{
  new (&_storage) iscool::style::declaration(std::move(*that));
}

iscool::style::detail::declaration_ref::~declaration_ref()
{
  (**this).~declaration();
}

iscool::style::detail::declaration_ref&
iscool::style::detail::declaration_ref::operator=(const declaration_ref& that)
{
  **this = *that;
  return *this;
}

iscool::style::detail::declaration_ref&
iscool::style::detail::declaration_ref::operator=(declaration_ref&& that)
{
  if (this == &that)
    return *this;

  **this = std::move(*that);
  return *this;
}

iscool::style::declaration& iscool::style::detail::declaration_ref::operator*()
{
  return *reinterpret_cast<declaration*>(&_storage);
}

const iscool::style::declaration&
iscool::style::detail::declaration_ref::operator*() const
{
  return *reinterpret_cast<const declaration*>(&_storage);
}

iscool::style::declaration*
iscool::style::detail::declaration_ref::operator->()
{
  return &this->operator*();
}

const iscool::style::declaration*
iscool::style::detail::declaration_ref::operator->() const
{
  return &this->operator*();
}

iscool::style::detail::declaration_ref::operator iscool::style::declaration&()
{
  return **this;
}

iscool::style::detail::declaration_ref::operator const iscool::style::
    declaration&() const
{
  return **this;
}
