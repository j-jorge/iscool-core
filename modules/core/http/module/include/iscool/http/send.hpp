// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/error_handler.hpp>
#include <iscool/http/response_handler.hpp>

#include <iscool/signals/shared_connection_set.hpp>

namespace iscool
{
  namespace http
  {
    iscool::signals::shared_connection_set get(const std::string& url,
                                               response_handler on_result,
                                               error_handler on_error);

    iscool::signals::shared_connection_set
    post(const std::string& url, std::vector<std::string> headers,
         std::string body, response_handler on_result, error_handler on_error);
  }
}
