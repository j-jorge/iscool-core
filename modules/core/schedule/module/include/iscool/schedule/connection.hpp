// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/signals/connection.hpp>

namespace iscool::schedule
{
  namespace detail
  {
    class delayed_call_manager;
  }

  class connection
  {
    friend class detail::delayed_call_manager;

  public:
    connection();

    bool connected() const;
    void disconnect();

  private:
    explicit connection(iscool::signals::connection c);

  private:
    iscool::signals::connection _signal_connection;
  };
}
