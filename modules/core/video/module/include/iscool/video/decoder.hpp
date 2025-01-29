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
#ifndef ISCOOL_VIDEO_DECODER_H
#define ISCOOL_VIDEO_DECODER_H

#include <iscool/video/video_info.hpp>

#include <iscool/optional.hpp>
#include <iscool/signals/declare_signal.hpp>

#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

namespace iscool
{
  namespace video
  {
    namespace detail
    {
      struct decoder_state
      {
        std::condition_variable update_condition;
        std::mutex mutex;
        bool quit;
        bool need_update;
      };
    }

    class decoder
    {
    public:
      using rgb24_data_pointer = std::uint8_t*;

      DECLARE_SIGNAL(void(rgb24_data_pointer), frame_ready, _frame_ready)

    public:
      decoder();
      ~decoder();

      decoder(const decoder&) = delete;
      decoder& operator=(const decoder&) = delete;

      iscool::optional<video_info> decode(const std::string& path);
      void consume_frame();

    private:
      void terminate_thread();

    private:
      detail::decoder_state _decoder_state;
      std::thread _thread;
    };
  }
}

#endif
