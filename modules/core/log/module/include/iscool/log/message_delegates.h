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
#ifndef ISCOOL_LOG_MESSAGE_DELEGATES_H
#define ISCOOL_LOG_MESSAGE_DELEGATES_H

#include <functional>
#include <string>

namespace iscool
{
  namespace error
  {
    class synopsis;
  }

  namespace log
  {
    namespace nature
    {
      class nature;
    }

    class context;

    class message_delegates
    {
    public:
      bool is_valid() const;

    public:
      std::function<void(const nature::nature&, const context&,
                         const std::string&)>
          print_message;

      std::function<void(const context&, const error::synopsis&)> print_error;
    };
  }
}

#endif
