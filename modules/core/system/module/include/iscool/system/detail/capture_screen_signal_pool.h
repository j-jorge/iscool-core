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
#ifndef ISCOOL_SYSTEM_DETAIL_CAPTURE_SCREEN_SIGNAL_POOL_H
#define ISCOOL_SYSTEM_DETAIL_CAPTURE_SCREEN_SIGNAL_POOL_H

#include "iscool/memory/dynamic_pool.h"
#include "iscool/memory/pool_signal_traits.h"
#include "iscool/system/detail/capture_screen_signal.h"

#include <utility>

namespace iscool
{
  namespace system
  {
    namespace detail
    {
      class capture_screen_signal_pool
      {
      private:
        typedef iscool::memory::dynamic_pool<
            capture_screen_signal,
            iscool::memory::pool_signal_traits<capture_screen_signal>>
            pool_type;

      public:
        typedef pool_type::slot slot;

      public:
        explicit capture_screen_signal_pool(std::size_t size);

        slot pick_available_signal();

        void process_capture(std::size_t signal_index,
                             const std::string& path);

      private:
        pool_type _pool;
      };
    }
  }
}

#endif
