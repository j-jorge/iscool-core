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
#pragma once

#include <string>
#include <string_view>

namespace iscool::log
{
  namespace nature
  {
    class nature;
  }

  class context;

  namespace detail
  {
    void set_android_tag(const std::string_view& tag);
    void print_to_console(const nature::nature& nature, const context& context,
                          const std::string& message);
  }
}
