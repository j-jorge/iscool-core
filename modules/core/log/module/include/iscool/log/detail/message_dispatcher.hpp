// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/log/context.hpp>
#include <iscool/log/message_delegates.hpp>
#include <iscool/log/nature/nature.hpp>

#include <format>
#include <mutex>
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
                      std::format_string<Args...> pattern, Args&&... args);

        void dispatch_error(const context& context,
                            const error::synopsis& synopsis);

      private:
        void dispatch_to_delegates(const nature::nature& nature,
                                   const context& context,
                                   const std::string& message);

      private:
        std::mutex _mutex;
        std::size_t _next_id;
        std::unordered_map<std::size_t, message_delegates> _delegates;

        std::string _message;

        std::size_t _last_message_counter;
        nature::nature _last_nature;
        context _last_context;
        std::string _last_message;
      };
    }
  }
}
