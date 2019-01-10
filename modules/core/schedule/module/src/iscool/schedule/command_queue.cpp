#include "iscool/schedule/command_queue.h"

#include <cassert>

iscool::schedule::command_queue::command_queue()
    : _next( 0 )
{
    
}

bool iscool::schedule::command_queue::empty() const
{
    return _next == _commands.size();
}

void iscool::schedule::command_queue::clear()
{
    _next = 0;
    _commands.clear();
}

void iscool::schedule::command_queue::execute_next()
{
    assert( _next < _commands.size() );

    const std::size_t i( _next );
    ++_next;

    _commands[ i ]();
}
