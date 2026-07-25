// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/error_handler.hpp>
#include <iscool/http/json/response_handler.hpp>

#include <iscool/signals/shared_connection_set.hpp>

namespace iscool::http::json
{
  iscool::signals::shared_connection_set get(std::string url,
                                             response_handler on_result,
                                             http::error_handler on_error);

  iscool::signals::shared_connection_set post(std::string url,
                                              const Json::Value& body,
                                              response_handler on_result,
                                              http::error_handler on_error);
}
