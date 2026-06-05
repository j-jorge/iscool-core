// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/response_handler.hpp>

#include <json/value.h>

namespace iscool::http::json
{
  typedef std::function<void(const Json::Value&)> response_handler;
}
