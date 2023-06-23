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
#ifndef SCOPEDPOWER_H
#define SCOPEDPOWER_H

#include "iscool/wish/genie.h"

namespace iscool
{
  namespace wish
  {
    template <typename T>
    class scoped_power
    {
    public:
      scoped_power(genie& main_genie, std::function<void(const T&)> function);

      ~scoped_power();

      scoped_power<T>& operator=(const scoped_power<T>&) = delete;
      scoped_power(const scoped_power<T>&) = delete;

    private:
      genie& _genie;
    };
  }
}

#include "iscool/wish/scoped_power.tpp"

#endif
