// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/request_connection.hpp>

#include <iscool/memory/dynamic_pool.hpp>

namespace iscool::http
{
  namespace detail
  {
    struct request_connection_traits;
  }

  struct request_connection;

  using request_connection_pool =
      iscool::memory::dynamic_pool<request_connection,
                                   detail::request_connection_traits>;
}

extern template class iscool::memory::dynamic_pool<
    iscool::http::request_connection,
    iscool::http::detail::request_connection_traits>;
