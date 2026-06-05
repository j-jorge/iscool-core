// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <functional>

namespace iscool::http
{
  class request;

  typedef std::function<void(request)> send_function;
}
