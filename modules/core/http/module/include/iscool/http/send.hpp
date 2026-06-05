// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/response_handler.hpp>

#include <iscool/signals/shared_connection_set.hpp>

namespace iscool
{
  namespace http
  {
    iscool::signals::shared_connection_set get(std::string url,
                                               response_handler on_result,
                                               response_handler on_error);

    iscool::signals::shared_connection_set
    post(std::string url, std::vector<std::string> headers, std::string body,
         response_handler on_result, response_handler on_error);
  }
}
