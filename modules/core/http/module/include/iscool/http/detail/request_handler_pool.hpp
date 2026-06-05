// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/detail/request_handler.hpp>
#include <iscool/memory/dynamic_pool.hpp>

#include <utility>

namespace iscool::http::detail
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
