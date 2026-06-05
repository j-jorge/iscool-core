// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <span>

namespace iscool::http
{
  struct response
  {
    int status;
    std::span<const char> body;
  };
}
