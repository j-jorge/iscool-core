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
#ifndef ISCOOL_HTTP_DETAIL_REQUEST_HANDLER_POOL_H
#define ISCOOL_HTTP_DETAIL_REQUEST_HANDLER_POOL_H

#include "iscool/http/detail/request_handler.h"
#include "iscool/memory/dynamic_pool.h"

#include <utility>

namespace iscool
{
  namespace http
  {
    namespace detail
    {
      struct request_handler_pool_traits;

      class request_handler_pool
      {
      private:
        typedef iscool::memory::dynamic_pool<request_handler,
                                             request_handler_pool_traits>
            pool_type;

      public:
        typedef pool_type::slot slot;

      public:
        explicit request_handler_pool(std::size_t size);

        slot pick_available_handler();

        void process_response(std::size_t handler_index, const response& r);

      private:
        pool_type _pool;
      };
    }
  }
}

#endif
