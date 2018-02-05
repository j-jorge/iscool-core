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
#ifndef ISCOOL_HTTP_SEND_H
#define ISCOOL_HTTP_SEND_H

#include "iscool/http/response_handler.h"

#include "iscool/signals/shared_connection_set.h"

namespace iscool
{
    namespace http
    {
        iscool::signals::shared_connection_set get
        ( const std::string& url,
          response_handler on_result, response_handler on_error );

        iscool::signals::shared_connection_set post
        ( const std::string& url, const std::vector<std::string>& headers,
          const std::string& body,
          response_handler on_result, response_handler on_error );
    }
}

#endif
