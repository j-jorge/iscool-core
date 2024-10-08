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
#include <iscool/signals/statistics_sink.hpp>

#include <iscool/signals/detail/statistics_function.hpp>

void iscool::signals::set_statistics_sink(
    const std::function<void(const statistics_data&)>& sink)
{
  assert(sink);
  detail::statistics_function = sink;
}

void iscool::signals::clear_statistics_sink()
{
  detail::statistics_function = std::function<void(const statistics_data&)>();
}
