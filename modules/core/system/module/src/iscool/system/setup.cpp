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
#include <iscool/system/setup.hpp>

#include <iscool/system/detail/capture_screen_delegate.hpp>

void iscool::system::initialize(capture_screen_function delegate)
{
  assert(delegate);
  assert(!detail::capture_screen_delegate);
  detail::capture_screen_delegate = delegate;
}

void iscool::system::finalize()
{
  detail::capture_screen_delegate = capture_screen_function();
}
