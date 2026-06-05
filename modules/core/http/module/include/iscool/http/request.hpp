// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/response.hpp>

#include <functional>
#include <string>
#include <vector>

namespace iscool::http
{
  struct request
  {
    enum class type
    {
      get,
      post
    };

    typedef std::function<void(const response&)> response_handler;

    type request_type;
    std::string url;
    std::string body;
    std::vector<std::string> headers;
    response_handler result_handler;
  };
}
