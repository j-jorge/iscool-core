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
#pragma once

#include <iscool/schedule/delayed_call.hpp>

template <typename Signature>
iscool::schedule::async_signal<Signature>::async_signal::~async_signal()
{
  for (iscool::signals::connection& c : _trigger_connection)
    c.disconnect();
}

template <typename Signature>
iscool::signals::connection iscool::schedule::async_signal<Signature>::connect(
    const std::function<Signature>& f)
{
  return _signal.connect(f);
}

template <typename Signature>
template <typename... Arg>
void iscool::schedule::async_signal<Signature>::operator()(Arg... args)
{
  _trigger_connection.push_back(
      delayed_call(std::bind(&async_signal<Signature>::trigger_signal<Arg...>,
                             this, std::forward<Arg>(args)...)));
}

template <typename Signature>
template <typename... Arg>
void iscool::schedule::async_signal<Signature>::trigger_signal(Arg... args)
{
  assert(!_trigger_connection.empty());
  _trigger_connection.erase(_trigger_connection.begin());
  _signal(std::forward<Arg>(args)...);
}
