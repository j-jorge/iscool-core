#ifndef ISCOOL_SCHEDULE_COMMAND_QUEUE_H
#define ISCOOL_SCHEDULE_COMMAND_QUEUE_H

#include <functional>
#include <vector>

namespace iscool
{
  namespace schedule
  {
    class command_queue
    {
    public:
      command_queue();

      bool empty() const;
      void clear();

      template <typename F, typename... Args>
      void queue(F&& callback, Args&&... args);

      void execute_next();

    private:
      std::vector<std::function<void()>> _commands;
      std::size_t _next;
    };
  }
}

#include <iscool/schedule/detail/command_queue.tpp>

#endif
