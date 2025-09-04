// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/schedule/connection.hpp>
#include <iscool/signals/declare_signal.hpp>

#include <functional>

namespace iscool::schedule
{
  template <typename Signature>
  class async_signal
  {
  public:
    ~async_signal();

    iscool::signals::connection connect(const std::function<Signature>& f);

    template <typename... Arg>
    void operator()(Arg&&... args);

  private:
    template <typename... Arg>
    void trigger_signal(Arg&&... args);

  private:
    typedef iscool::signals::signal<Signature> signal_type;

  private:
    signal_type _signal;
    std::vector<connection> _trigger_connection;
  };
}

#define DECLARE_ASYNC_SIGNAL(TYPE, NAME, MEMBER)                              \
public:                                                                       \
  typedef std::function<TYPE> DETAIL_SIGNAL_FUNCTION_TYPE_NAME(NAME);         \
                                                                              \
  ::iscool::signals::connection DETAIL_SIGNAL_CONNECT_FUNCTION_NAME(NAME)(    \
      const DETAIL_SIGNAL_FUNCTION_TYPE_NAME(NAME) & function) const;         \
                                                                              \
private:                                                                      \
  mutable ::iscool::schedule::async_signal<TYPE> MEMBER;

#define DECLARE_ASYNC_VOID_SIGNAL(NAME, MEMBER)                               \
  DECLARE_ASYNC_SIGNAL(void(), NAME, MEMBER)

#include <iscool/schedule/detail/async_signal.tpp>
