// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/schedule/connection.hpp>

#include <deque>
#include <functional>

namespace iscool::schedule
{
  template <typename Signature>
  class async_function
  {
  public:
    async_function();

    template <typename F>
    async_function(const F& f);
    async_function(const async_function<Signature>& that);
    ~async_function();

    async_function<Signature>&
    operator=(const async_function<Signature>& that);

    template <typename... Args>
    void operator()(Args... args);

    bool empty() const;

  private:
    template <typename... Args>
    void trigger(Args... args);

  private:
    std::deque<connection> _connections;
    std::function<Signature> _function;
  };
}

#include <iscool/schedule/detail/async_function.tpp>
