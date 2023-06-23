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
#include "iscool/http/detail/request_handler_pool.h"

namespace iscool
{
  namespace http
  {
    namespace detail
    {
      struct request_handler_pool_traits
      {
        static bool clear(request_handler& h);
      };
    }
  }
}

iscool::http::detail::request_handler_pool::request_handler_pool(
    std::size_t size)
  : _pool(size)
{}

iscool::http::detail::request_handler_pool::slot
iscool::http::detail::request_handler_pool::pick_available_handler()
{
  return _pool.pick_available();
}

void iscool::http::detail::request_handler_pool::process_response(
    std::size_t handler_index, const response& r)
{
  _pool.get(handler_index).process_response(r);
  _pool.release(handler_index);
}

bool iscool::http::detail::request_handler_pool_traits::clear(
    request_handler& h)
{
  h.clear();
  return true;
}
