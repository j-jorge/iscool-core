// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/request_connection_pool.hpp>

#include <iscool/memory/dynamic_pool.impl.hpp>

struct iscool::http::detail::request_connection_traits
{
  static bool clear(request_connection& r)
  {
    r.disconnect();
    return true;
  }
};

template class iscool::memory::dynamic_pool<
    iscool::http::request_connection,
    iscool::http::detail::request_connection_traits>;
