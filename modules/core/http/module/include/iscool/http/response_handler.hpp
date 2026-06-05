// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <functional>
#include <span>

namespace iscool::http
{
  typedef std::function<void(std::span<const char>)> response_handler;
}
