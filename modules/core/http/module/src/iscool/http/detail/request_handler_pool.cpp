// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/detail/request_handler_pool.hpp>

namespace iscool::http::detail
{
  struct request_handler_pool_traits
  {
    static bool clear(request_handler& h);
  };
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

iscool::http::detail::request_handler&
iscool::http::detail::request_handler_pool::get(std::size_t handler_index)
{
  return _pool.get(handler_index);
}

void iscool::http::detail::request_handler_pool::release(
    std::size_t handler_index)
{
  _pool.release(handler_index);
}

bool iscool::http::detail::request_handler_pool_traits::clear(
    request_handler& h)
{
  h.clear();
  return true;
}
