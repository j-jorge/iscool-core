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
#ifndef ISCOOL_FACTORY_DYNAMIC_FACTORY_IMPL_TPP
#define ISCOOL_FACTORY_DYNAMIC_FACTORY_IMPL_TPP

#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>

#include <cassert>

template <typename T, typename... A>
void iscool::factory::dynamic_factory<T, A...>::register_typename(
    std::string name, dynamic_factory_function creator)
{
  assert(_factory.find(name) == _factory.end());
  assert(creator);
  _factory.insert(std::make_pair(std::move(name), std::move(creator)));
}

template <typename T, typename... A>
T iscool::factory::dynamic_factory<T, A...>::create_by_typename(
    std::string_view name, A... arguments) const
{
  const auto it(_factory.find(name));

  if (it == _factory.end())
    {
      ic_log(iscool::log::nature::error(), "iscool::factory::dynamic_factory",
             "Type not found in factory: {}", name);
      assert(false);
    }

  return it->second(arguments...);
}

#endif
