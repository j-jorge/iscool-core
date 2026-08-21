// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/signals/scoped_connection.hpp>

namespace iscool::http
{
  struct request_connection
  {
    bool connected() const;
    void disconnect();

    iscool::signals::scoped_connection result;
    iscool::signals::scoped_connection error;
  };
}
