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
#ifndef ISCOOL_FACTORY_DYNAMIC_FACTORY_H
#define ISCOOL_FACTORY_DYNAMIC_FACTORY_H

#include <iscool/factory/factory_function.hpp>

#include <string>
#include <unordered_map>

namespace iscool
{
  namespace factory
  {
    template <typename T, typename... A>
    class dynamic_factory
    {
    public:
      typedef factory_function<T, A...> dynamic_factory_function;

    public:
      void register_typename(const std::string& name,
                             const dynamic_factory_function& creator);

      T create_by_typename(const std::string& name, A... arguments) const;

    private:
      std::unordered_map<std::string, dynamic_factory_function> _factory;
    };
  }
}

#endif
