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
#ifndef ISCOOL_CORE_FACTORY_DYNAMIC_FACTORY_REGISTRAR_H
#define ISCOOL_CORE_FACTORY_DYNAMIC_FACTORY_REGISTRAR_H

#include "iscool/factory/factory_function.h"

#include <string>

namespace iscool
{
  namespace factory
  {
    template <typename T, typename... A>
    class dynamic_factory;

    template <typename T, typename... A>
    class dynamic_factory_registrar
    {
    public:
      dynamic_factory_registrar(dynamic_factory<T, A...>& factory,
                                const std::string& name,
                                const factory_function<T, A...>& creator);
    };
  }
}

#include "iscool/factory/detail/dynamic_factory_registrar.tpp"

#endif
