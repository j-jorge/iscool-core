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
#ifndef ISCOOL_LOG_DETAIL_MESSAGE_DISPATCHER_H
#define ISCOOL_LOG_DETAIL_MESSAGE_DISPATCHER_H

#include <iscool/log/message_delegates.hpp>

#include <unordered_map>

namespace iscool
{
  namespace error
  {
    class synopsis;
  }

  namespace log
  {
    namespace nature
    {
      class nature;
    }

    namespace detail
    {
      class message_dispatcher
      {
      public:
        message_dispatcher();

        std::size_t register_delegates(const message_delegates& delegates);
        void unregister_delegates(std::size_t id);

        void clear();

        template <typename... Args>
        void dispatch(const nature::nature& nature, const context& context,
                      const char* pattern, Args&&... args) const;

        void dispatch_error(const context& context,
                            const error::synopsis& synopsis) const;

      private:
        void dispatch_to_delegates(const nature::nature& nature,
                                   const context& context,
                                   const std::string& message) const;

      private:
        std::size_t _next_id;
        std::unordered_map<std::size_t, message_delegates> _delegates;
      };
    }
  }
}

#endif
