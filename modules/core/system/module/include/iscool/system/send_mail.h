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
#ifndef ISCOOL_SYSTEM_SEND_MAIL_H
#define ISCOOL_SYSTEM_SEND_MAIL_H

#include <string>

namespace iscool
{
    namespace system
    {
        void send_mail
        ( const std::string& address, const std::string& subject,
          const std::string& body );
    }
}

#endif
