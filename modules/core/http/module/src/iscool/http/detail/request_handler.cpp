// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/detail/request_handler.hpp>

#include <iscool/http/response.hpp>
#include <iscool/signals/implement_signal.hpp>

IMPLEMENT_SIGNAL(iscool::http::detail::request_handler, result, _on_result);
IMPLEMENT_SIGNAL(iscool::http::detail::request_handler, error, _on_error);

iscool::http::detail::request_handler::request_handler() = default;
iscool::http::detail::request_handler::~request_handler() = default;

void iscool::http::detail::request_handler::process_response(const response& r)
{
  if (r.status == 200)
    _on_result(r.body);
  else
    _on_error(r.body);
}

void iscool::http::detail::request_handler::clear()
{
  _on_result.disconnect_all_slots();
  _on_error.disconnect_all_slots();
}
