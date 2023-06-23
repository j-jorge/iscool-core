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
#ifndef WISHINGWELL_H
#define WISHINGWELL_H

#include <iscool/wish/genie.hpp>
#include <iscool/wish/wish.hpp>

namespace iscool
{
  namespace wish
  {
    class wishing_well
    {
    public:
      explicit wishing_well(genie& genie);

      template <typename T>
      void make_a_wish(const T& wish);

      template <typename T>
      void make_a_wish();

      template <typename T>
      bool is_wish_grantable();

    private:
      genie& _genie;
    };
  }
}

#include <iscool/wish/wishing_well.tpp>

#endif
