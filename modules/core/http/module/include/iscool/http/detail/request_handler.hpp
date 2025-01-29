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
#ifndef ISCOOL_HTTP_DETAIL_REQUEST_HANDLER_H
#define ISCOOL_HTTP_DETAIL_REQUEST_HANDLER_H

#include <iscool/signals/declare_signal.hpp>

namespace iscool
{
  namespace http
  {
    class response;

    namespace detail
    {
      class request_handler
      {
        DECLARE_SIGNAL(void(std::vector<char>), result, _on_result)
        DECLARE_SIGNAL(void(std::vector<char>), error, _on_error)

      public:
        request_handler();
        ~request_handler();

        void process_response(const response& r);
        void clear();
      };
    }
  }
}

#endif
