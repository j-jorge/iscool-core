// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/error_handler.hpp>
#include <iscool/http/request_connection.hpp>
#include <iscool/http/response_handler.hpp>

namespace iscool::http
{
  request_connection get(const std::string& url, response_handler on_result,
                         error_handler on_error);

  request_connection post(const std::string& url,
                          std::vector<std::string> headers, std::string body,
                          response_handler on_result, error_handler on_error);
}
