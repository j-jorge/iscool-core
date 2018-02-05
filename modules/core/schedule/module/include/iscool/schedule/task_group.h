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
#ifndef ISCOOL_SCHEDULE_TASK_GROUP_H
#define ISCOOL_SCHEDULE_TASK_GROUP_H

#include "iscool/schedule/worker.h"

#include <vector>

namespace iscool
{
    namespace schedule
    {
        class task_group
        {
        public:
            task_group();
            ~task_group();

            template< typename TaskType, typename... Args >
            void run( Args&&... args );

        private:
            void pop( std::size_t id );

            std::size_t get_available_task_index();
            
        private:
            std::vector< worker::handle > _tasks;
        };
    }
}

#endif
