// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/signals/connection.hpp>

namespace iscool::signals
{
  class scoped_connection
  {
  public:
    scoped_connection();
    scoped_connection(const connection& that);
    scoped_connection(connection&& that) noexcept;
    scoped_connection(const scoped_connection& that);
    scoped_connection(scoped_connection&& that) noexcept;
    ~scoped_connection();

    bool operator==(const scoped_connection& that) const;
    bool operator!=(const scoped_connection& that) const;

    bool operator!=(const connection& that) const;
    bool operator==(const connection& that) const;

    scoped_connection& operator=(const connection& that);
    scoped_connection& operator=(connection&& that) noexcept;
    scoped_connection& operator=(const scoped_connection& that);
    scoped_connection& operator=(scoped_connection&& that) noexcept;

    void disconnect() const;
    bool connected() const;

  private:
    connection _connection;
  };
}
