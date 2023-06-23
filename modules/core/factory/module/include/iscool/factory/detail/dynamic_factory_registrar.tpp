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
#ifndef ISCOOL_CORE_FACTORY_DYNAMIC_FACTORY_REGISTRAR_TPP
#define ISCOOL_CORE_FACTORY_DYNAMIC_FACTORY_REGISTRAR_TPP

#include <iscool/factory/dynamic_factory.hpp>

#include <cassert>

template <typename T, typename... A>
iscool::factory::dynamic_factory_registrar<T, A...>::dynamic_factory_registrar(
    dynamic_factory<T, A...>& factory, const std::string& name,
    const factory_function<T, A...>& creator)
{
  assert(creator);
  factory.register_typename(name, creator);
}

#endif
