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
#include <iscool/time/setup.hpp>

#include <iscool/time/detail/monotonic_time_source.hpp>
#include <iscool/time/detail/time_source.hpp>

#include <cassert>

void iscool::time::initialize(time_source_delegate time_source,
                              time_source_delegate monotonic_time_source)
{
  assert(time_source);
  assert(monotonic_time_source);

  detail::time_source = std::move(time_source);
  detail::monotonic_time_source = std::move(monotonic_time_source);
}

void iscool::time::finalize()
{
  detail::time_source = time_source_delegate();
  detail::monotonic_time_source = time_source_delegate();
}

iscool::time::scoped_time_source_delegate::scoped_time_source_delegate(
    time_source_delegate time_source,
    time_source_delegate monotonic_time_source)
{
  initialize(std::move(time_source), std::move(monotonic_time_source));
}

iscool::time::scoped_time_source_delegate::~scoped_time_source_delegate()
{
  finalize();
}
