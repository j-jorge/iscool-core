// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <functional>
#include <span>

namespace iscool::http
{
  typedef std::function<void(int, std::span<const char>)> error_handler;
}
