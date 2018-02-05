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
#ifndef ISCOOL_SCHEDULE_DETAIL_DELAYED_CALL_MANAGER_H
#define ISCOOL_SCHEDULE_DETAIL_DELAYED_CALL_MANAGER_H

#include "iscool/memory/dynamic_pool.h"
#include "iscool/memory/pool_signal_traits.h"
#include "iscool/schedule/short_call_policy.h"

#include "iscool/signals/signal.h"
#include "iscool/signals/void_signal_function.h"

#include <boost/thread/recursive_mutex.hpp>

#include <chrono>

namespace iscool
{
    namespace schedule
    {
        namespace detail
        {
            class delayed_call_manager
            {
            public:
                typedef std::chrono::milliseconds duration;

            public:
                explicit delayed_call_manager( std::size_t pool_size );

                iscool::signals::connection
                schedule_call
                ( iscool::signals::void_signal_function f, duration delay);

                iscool::signals::connection
                schedule_call
                ( iscool::signals::void_signal_function f,
                  short_call_policy policy );

                void clear();

            private:
                typedef
                iscool::memory::dynamic_pool
                <
                    iscool::signals::void_signal,
                    iscool::memory::pool_signal_traits
                    <
                        iscool::signals::void_signal
                    >
                >
                pool_type;

            private:
                iscool::signals::connection
                schedule_cumulated( iscool::signals::void_signal_function f );

                iscool::signals::connection
                schedule_non_cumulated
                ( iscool::signals::void_signal_function f );

                iscool::signals::connection
                schedule_delayed
                ( iscool::signals::void_signal_function f, duration delay );

                void schedule_client( std::size_t id, duration delay );
                void schedule_client_cumulated();
                void schedule_client_non_cumulated();

                void trigger( std::size_t id, duration expected_date );
                void trigger_cumulated();
                void trigger_non_cumulated();

            private:
                iscool::signals::void_signal _short_call_cumulated;
                iscool::signals::void_signal _short_call_non_cumulated;
                pool_type _pool;

                bool _client_guard;
                bool _in_cumulated_loop;

                boost::recursive_mutex _mutex;
            };
        }
    }
}

#endif
