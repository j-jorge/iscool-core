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
#ifndef ISCOOL_MONITORING_PROGRESS_MONITOR_H
#define ISCOOL_MONITORING_PROGRESS_MONITOR_H

#include "iscool/signals/signal.h"

#include <cstdint>
#include <functional>

namespace iscool
{
  namespace monitoring
  {
    class progress_monitor
    {
    public:
      progress_monitor();
      progress_monitor(progress_monitor&& that);
      progress_monitor(progress_monitor& master, std::uint32_t range);

      signals::connection
      connect_to_updated(std::function<void(float)> f) const;

      void begin_monitoring(std::uint32_t steps);
      void worked(std::uint32_t count);
      void done();

      bool is_started() const;

    private:
      void internal_worked(float count);
      std::uint32_t get_remaining_range() const;

    private:
      progress_monitor* const _master;
      const std::uint32_t _range;
      std::uint32_t _steps;
      float _progress;

      mutable iscool::signals::signal<void(float)> _updated;
    };
  }
}

#endif
