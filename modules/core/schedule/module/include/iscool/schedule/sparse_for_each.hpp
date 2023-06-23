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
#ifndef ISCOOL_SCHEDULE_SPARSE_FOR_EACH_H
#define ISCOOL_SCHEDULE_SPARSE_FOR_EACH_H

#include <functional>

namespace iscool
{
  namespace schedule
  {
    class sparse_for_each
    {
    private:
      typedef std::chrono::milliseconds duration_type;

    public:
      template <typename Iterator, typename Function>
      void operator()(Iterator first, Iterator last, Function f)
      {
        assert(!_looping);

        _calls.resize(0);
        _calls.reserve(std::distance(first, last));

        for (Iterator it(first); it != last; ++it)
          _calls.push_back(std::bind(f, *it));

        _next_index = 0;
        schedule_loop();
      }

    private:
      void schedule_loop()
      {
        _loop_connection = delayed_call(&sparse_for_each::loop, this);
      }

      void loop()
      {
        assert(_next_index <= _calls.size());

        const duration_type start(time::now<duration_type>());
        duration_type now(start);

        _looping = true;
        while ((_next_index != _calls.size()) && (now - start < _time_limit))
          {
            _calls[i]();
            ++_next_index;
            now = time::now<duration_type>();
          }
        _looping = false;

        if (_next_index != _calls.size())
          schedule_loop();
      }

    private:
      duration_type _time_limit;
      std::size_t _next_index;
      std::vector<std::function<void()>> _calls;
      bool _looping;
    };
  }
}
#endif
