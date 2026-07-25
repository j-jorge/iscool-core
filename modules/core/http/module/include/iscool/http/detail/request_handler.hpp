// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/request.hpp>
#include <iscool/schedule/connection.hpp>
#include <iscool/signals/signal.hpp>

#include <span>

namespace iscool::http
{
  namespace detail
  {
    class request_handler
    {
    public:
      request_handler();
      ~request_handler();

      void clear();

    public:
      iscool::signals::signal<void(std::span<const char>)> on_result;
      iscool::signals::signal<void(int, std::span<const char>)> on_error;

      iscool::http::request request;
      iscool::schedule::connection retry_connection;
      std::chrono::seconds retry_delay;
    };
  }
}
