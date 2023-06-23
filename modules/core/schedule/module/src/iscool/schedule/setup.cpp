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
#include <iscool/schedule/setup.hpp>

#include <iscool/schedule/detail/call_later.hpp>

#include <cassert>

void iscool::schedule::initialize(delayed_call_delegate delegate)
{
  assert(!detail::call_later);
  assert(delegate);

  detail::call_later = std::move(delegate);
}

void iscool::schedule::finalize()
{
  detail::call_later = delayed_call_delegate();
  detail::call_manager.clear();
}

iscool::schedule::scoped_scheduler_delegate::scoped_scheduler_delegate(
    delayed_call_delegate delegate)
{
  initialize(std::move(delegate));
}

iscool::schedule::scoped_scheduler_delegate::~scoped_scheduler_delegate()
{
  finalize();
}
