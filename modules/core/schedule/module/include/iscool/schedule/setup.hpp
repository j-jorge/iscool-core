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
#ifndef ISCOOL_SCHEDULE_SETUP_H
#define ISCOOL_SCHEDULE_SETUP_H

#include <iscool/schedule/delayed_call_delegate.hpp>

namespace iscool
{
  namespace schedule
  {
    void initialize(delayed_call_delegate delegate);
    void finalize();

    class scoped_scheduler_delegate
    {
    public:
      explicit scoped_scheduler_delegate(delayed_call_delegate delegate);
      scoped_scheduler_delegate(const scoped_scheduler_delegate&) = delete;
      ~scoped_scheduler_delegate();

      scoped_scheduler_delegate&
      operator=(const scoped_scheduler_delegate&) = delete;
    };
  }
}

#endif
