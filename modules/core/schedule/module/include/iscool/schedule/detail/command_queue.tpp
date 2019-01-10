#ifndef ISCOOL_SCHEDULE_COMMAND_QUEUE_TPP
#define ISCOOL_SCHEDULE_COMMAND_QUEUE_TPP

template< typename F, typename... Args >
void iscool::schedule::command_queue::queue( F&& callback, Args&&... args )
{
    _commands.emplace_back
        ( std::bind
          ( std::forward< F >( callback ), std::forward< Args >( args )... ) );
}

#endif
