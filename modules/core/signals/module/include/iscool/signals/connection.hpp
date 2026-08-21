// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/signals/detail/slot.hpp>

#include <memory>

namespace iscool::signals
{
  class connection
  {
  public:
    connection();
    explicit connection(const std::weak_ptr<detail::slot>& slot);
    connection(const connection& that);
    connection(connection&& that) noexcept;
    ~connection();

    connection& operator=(const connection& that);
    connection& operator=(connection&& that) noexcept;

    bool operator==(const connection& that) const;
    bool operator!=(const connection& that) const;

    bool connected() const;
    void disconnect() const;

  private:
    std::weak_ptr<detail::slot> _slot;
  };
}
