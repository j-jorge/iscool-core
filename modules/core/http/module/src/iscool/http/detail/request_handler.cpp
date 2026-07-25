// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/detail/request_handler.hpp>

#include <iscool/signals/signal.impl.tpp>

iscool::http::detail::request_handler::request_handler()
  : retry_delay(0)
{}

iscool::http::detail::request_handler::~request_handler() = default;

void iscool::http::detail::request_handler::clear()
{
  request.url.clear();
  request.body.clear();
  request.headers.clear();
  request.result_handler = {};

  retry_connection.disconnect();
  retry_delay = std::chrono::seconds(0);

  on_result.disconnect_all_slots();
  on_error.disconnect_all_slots();
}
