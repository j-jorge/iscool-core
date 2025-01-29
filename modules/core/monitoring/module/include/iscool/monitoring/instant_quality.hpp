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
#pragma once

#include <iscool/signals/declare_signal.hpp>

#include <vector>

namespace iscool
{
  namespace monitoring
  {
    class instant_quality
    {
      DECLARE_SIGNAL(void(float), quality_changed, _quality_changed)

    public:
      explicit instant_quality(std::size_t log_length);
      ~instant_quality();

      void reset();

      float get_last_measure() const;

      void add_attempt();

      void add_success();
      void add_failure();

    private:
      void update_quality_level(bool success);
      void queue_result(bool success);

    private:
      std::vector<bool> _result_log;
      std::size_t _next_result_slot;
      std::size_t _last_quality_level;
      std::size_t _attempts;
    };
  }
}
