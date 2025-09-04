// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/schedule/delayed_call.hpp>

template <typename Signature>
iscool::schedule::async_function<Signature>::async_function()
{}

template <typename Signature>
template <typename F>
iscool::schedule::async_function<Signature>::async_function(const F& f)
  : _function(f)
{}

template <typename Signature>
iscool::schedule::async_function<Signature>::async_function(
    const async_function<Signature>& that)
  : _function(that._function)
{}

template <typename Signature>
iscool::schedule::async_function<Signature>::async_function::~async_function()
{
  for (connection& c : _connections)
    c.disconnect();
}

template <typename Signature>
iscool::schedule::async_function<Signature>&
iscool::schedule::async_function<Signature>::operator=(
    const async_function<Signature>& that)
{
  _function = that._function;
  return *this;
}

template <typename Signature>
template <typename... Args>
void iscool::schedule::async_function<Signature>::operator()(Args... args)
{
  _connections.push_back(
      delayed_call(std::bind(&async_function<Signature>::trigger<Args...>,
                             this, std::forward<Args>(args)...)));
}

template <typename Signature>
bool iscool::schedule::async_function<Signature>::empty() const
{
  return !_function;
}

template <typename Signature>
template <typename... Args>
void iscool::schedule::async_function<Signature>::trigger(Args... args)
{
  _connections.pop_front();
  _function(std::forward<Args>(args)...);
}
