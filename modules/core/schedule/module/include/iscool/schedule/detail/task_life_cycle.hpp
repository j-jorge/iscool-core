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
#ifndef ISCOOL_SCHEDULE_DETAIL_TASK_LIFE_CYCLE_H
#define ISCOOL_SCHEDULE_DETAIL_TASK_LIFE_CYCLE_H

#include <iscool/schedule/task.hpp>

namespace iscool
{
  namespace schedule
  {
    namespace detail
    {
      class task_life_cycle
      {
        DECLARE_VOID_SIGNAL(complete, _complete);

      public:
        typedef std::unique_ptr<task> task_pointer;

      public:
        explicit task_life_cycle(task_pointer implementation);
        ~task_life_cycle();

        void start();
        void update();
        void abort();

        bool is_running() const;
        std::chrono::milliseconds get_update_interval() const;

      private:
        void complete();

      private:
        enum class state
        {
          created,
          running,
          stopped
        };

      private:
        state _internal_state;
        task_pointer _implementation;
      };
    }
  }
}

#endif
