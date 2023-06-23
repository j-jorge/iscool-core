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
#include <iscool/style/detail/shared_properties.hpp>

#include <cassert>

std::uint64_t iscool::style::detail::shared_properties::_next_id(0);

iscool::style::detail::shared_properties::shared_properties()
  : _reference_count(0)
{
  set_id();
}

std::uint64_t iscool::style::detail::shared_properties::get_id() const
{
  return _id;
}

void iscool::style::detail::shared_properties::reuse()
{
  assert(_reference_count == 0);
  values = properties();

  set_id();
}

void iscool::style::detail::shared_properties::add_reference()
{
  ++_reference_count;
}

void iscool::style::detail::shared_properties::remove_reference()
{
  assert(_reference_count != 0);
  --_reference_count;
}

bool iscool::style::detail::shared_properties::is_dangling()
{
  return _reference_count == 0;
}

std::size_t iscool::style::detail::shared_properties::get_use_count() const
{
  return _reference_count;
}

void iscool::style::detail::shared_properties::set_id()
{
  _id = _next_id;
  ++_next_id;
}
