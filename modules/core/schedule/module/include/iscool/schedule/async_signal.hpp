/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#ifndef ISCOOL_SCHEDULE_ASYNC_SIGNAL_H
#define ISCOOL_SCHEDULE_ASYNC_SIGNAL_H

#include <iscool/signals/declare_signal.hpp>

#include <functional>

namespace iscool
{
  namespace schedule
  {
    template <typename Signature>
    class async_signal
    {
    public:
      ~async_signal();

      iscool::signals::connection connect(const std::function<Signature>& f);

      template <typename... Arg>
      void operator()(Arg... args);

    private:
      template <typename... Arg>
      void trigger_signal(Arg... args);

    private:
      typedef iscool::signals::signal<Signature> signal_type;

    private:
      signal_type _signal;
      std::vector<iscool::signals::connection> _trigger_connection;
    };
  }
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

#endif
