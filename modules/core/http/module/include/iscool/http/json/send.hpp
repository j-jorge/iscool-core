// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/error_handler.hpp>
#include <iscool/http/json/response_handler.hpp>
#include <iscool/http/request_connection.hpp>

#include <string>
#include <vector>

namespace iscool::http::json
{
  request_connection get(const std::string& url, response_handler on_result,
                         http::error_handler on_error);

  request_connection post(const std::string& url, const Json::Value& body,
                          response_handler on_result,
                          http::error_handler on_error);

  request_connection post(const std::string& url,
                          std::vector<std::string> headers,
                          const Json::Value& body, response_handler on_result,
                          http::error_handler on_error);
}
