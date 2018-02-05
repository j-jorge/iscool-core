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
#ifndef ISCOOL_MONITORING_IMPLEMENT_PROGRESS_TRACKER_H
#define ISCOOL_MONITORING_IMPLEMENT_PROGRESS_TRACKER_H

#define ic_monitoring_implement_progress_tracker( scope, type )      \
    scope::type::type()                                              \
        : _done_steps( 0 )                                           \
    {                                                                \
                                                                     \
    }                                                                \
                                                                     \
    scope::type::type                                                \
    ( const boost::function< void() >& on_completed )                \
        : _notify_completed( on_completed ),                         \
          _done_steps( 0 )                                           \
    {                                                                \
                                                                     \
    }                                                                \
                                                                     \
    void scope::type::done( step s )                                 \
    {                                                                \
        assert( _notify_completed );                                 \
        const bit_field step_value( static_cast< bit_field >( s ) ); \
                                                                     \
        assert( ( _done_steps & step_value ) == 0 );                 \
        _done_steps |= step_value;                                   \
                                                                     \
        if ( _done_steps == all_mask )                               \
            _notify_completed();                                     \
    }                                                                \
                                                                     \
    void scope::type::reset()                                        \
    {                                                                \
        _done_steps = 0;                                             \
    }                                                                \
                                                                     \
    void scope::type::reset                                          \
    ( const boost::function< void() >& on_completed )                \
    {                                                                \
        reset();                                                     \
        _notify_completed = on_completed;                            \
    }

#endif
