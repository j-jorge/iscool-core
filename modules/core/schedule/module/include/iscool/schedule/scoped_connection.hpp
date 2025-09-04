// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/schedule/connection.hpp>

namespace iscool::schedule
{
  class scoped_connection
  {
  public:
    scoped_connection();
    scoped_connection(connection c);
    scoped_connection(const scoped_connection& that) = delete;
    scoped_connection(scoped_connection&& that);
    ~scoped_connection();

    scoped_connection& operator=(const scoped_connection& that) = delete;
    scoped_connection& operator=(scoped_connection&& that);
    scoped_connection& operator=(const connection& c);

    bool connected() const;
    void disconnect();

  private:
    connection _connection;
  };
}
