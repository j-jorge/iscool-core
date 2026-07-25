// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/signals/declare_signal.hpp>

#include <span>

namespace iscool::http
{
  class response;

  namespace detail
  {
    class request_handler
    {
      DECLARE_SIGNAL(void(std::span<const char>), result, _on_result)
      DECLARE_SIGNAL(void(int, std::span<const char>), error, _on_error)

    public:
      request_handler();
      ~request_handler();

      void process_response(const response& r);
      void clear();
    };
  }
}
