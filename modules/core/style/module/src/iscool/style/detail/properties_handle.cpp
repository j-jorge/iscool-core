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
#include <iscool/style/detail/properties_handle.hpp>

#include <iscool/style/detail/get_properties_pool.hpp>
#include <iscool/style/detail/shared_properties.hpp>

iscool::style::detail::properties_handle::properties_handle()
  : _properties(nullptr)
{}

iscool::style::detail::properties_handle::properties_handle(
    const properties_handle& that)
  : _pool_id(that._pool_id)
  , _properties(that._properties)
{
  if (_properties != nullptr)
    _properties->add_reference();
}

iscool::style::detail::properties_handle::properties_handle(
    properties_handle&& that)
  : _pool_id(that._pool_id)
  , _properties(that._properties)
{
  that._properties = nullptr;
}

iscool::style::detail::properties_handle::~properties_handle()
{
  reset();
}

iscool::style::detail::properties_handle&
iscool::style::detail::properties_handle::operator=(
    const properties_handle& that)
{
  if (this == &that)
    return *this;

  reset();

  _pool_id = that._pool_id;
  _properties = that._properties;

  if (_properties != nullptr)
    _properties->add_reference();

  return *this;
}

iscool::style::detail::properties_handle&
iscool::style::detail::properties_handle::operator=(properties_handle&& that)
{
  if (this == &that)
    return *this;

  reset();

  _pool_id = that._pool_id;
  _properties = that._properties;

  that._properties = nullptr;

  return *this;
}

iscool::style::detail::properties_handle::operator bool() const
{
  return _properties != nullptr;
}

iscool::style::detail::properties*
iscool::style::detail::properties_handle::operator->() const
{
  assert(_properties != nullptr);
  return &_properties->values;
}

iscool::style::detail::properties&
iscool::style::detail::properties_handle::operator*() const
{
  assert(_properties != nullptr);
  return _properties->values;
}

std::uint64_t iscool::style::detail::properties_handle::get_id() const
{
  assert(_properties != nullptr);
  return _properties->get_id();
}

void iscool::style::detail::properties_handle::alloc()
{
  reset();

  const auto slot(get_properties_pool().pick_available());
  _pool_id = slot.id;
  _properties = &slot.value;

  _properties->add_reference();
}

void iscool::style::detail::properties_handle::reset()
{
  if (_properties == nullptr)
    return;

  _properties->remove_reference();

  if (_properties->is_dangling())
    get_properties_pool().release(_pool_id);

  _properties = nullptr;
}

bool iscool::style::detail::properties_handle::is_unique() const
{
  return (_properties != nullptr) && (_properties->get_use_count() == 1);
}
