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
#ifndef ISCOOL_SCHEDULE_TASK_H
#define ISCOOL_SCHEDULE_TASK_H

#include <chrono>
#include <iscool/profile/profiler.hpp>
#include <iscool/signals/declare_signal.hpp>

namespace iscool
{
  namespace schedule
  {
    class task
    {
      DECLARE_VOID_SIGNAL(complete, _complete);

    public:
      static constexpr std::chrono::milliseconds no_update_interval{
        std::chrono::milliseconds::max()
      };

    public:
      explicit task(const std::string& name);
      virtual ~task();

      void start();
      void update();
      void abort();
      std::chrono::milliseconds get_update_interval() const;

    protected:
      void complete();
      void append_profile_tag(const std::string& tag);

    private:
      virtual void implementation_start();
      virtual void implementation_update();
      virtual void implementation_abort();
      virtual std::chrono::milliseconds
      implementation_get_update_interval() const;

      void end_profiler();

    private:
      iscool::profile::profiler _profiler;
      std::size_t _update_count;
    };
  }
}

#endif
