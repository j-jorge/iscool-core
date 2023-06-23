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
#ifndef GENIE_H
#define GENIE_H

#include <iscool/wish/wish.hpp>

#include <any>
#include <functional>
#include <map>

namespace iscool
{
  namespace wish
  {
    class genie
    {
    public:
      template <typename T>
      void empower(std::function<void(const T&)> function);

      template <typename T>
      void deny();

      template <typename T>
      void grant(const T& wish) const;

      template <typename T>
      bool is_wish_valid() const;

    private:
      typedef std::map<iscool::wish::kind, std::any> power_list;

    private:
      power_list _powers;
    };
  }
}

#include <iscool/wish/genie.tpp>

#endif
