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
#ifndef ISCOOL_SCHEDULE_ASYNC_FUNCTION_TPP
#define ISCOOL_SCHEDULE_ASYNC_FUNCTION_TPP

#include "iscool/schedule/delayed_call.h"


template< typename Signature >
iscool::schedule::async_function< Signature >::async_function()
{

}

template< typename Signature >
template< typename F >
iscool::schedule::async_function< Signature >::async_function( const F& f )
    : _function( f )
{

}

template< typename Signature >
iscool::schedule::async_function< Signature >::async_function
( const async_function< Signature >& that )
    : _function( that._function )
{

}

template< typename Signature >
iscool::schedule::async_function< Signature >::~async_function()
{
    for ( iscool::signals::connection& c : _connections )
        c.disconnect();
}

template< typename Signature >
iscool::schedule::async_function< Signature >&
iscool::schedule::async_function< Signature >::operator=
( const async_function< Signature >& that )
{
    _function = that._function;
    return *this;
}

template< typename Signature >
template< typename... Args >
void iscool::schedule::async_function< Signature >::operator()( Args... args )
{
    _connections.push_back
        ( delayed_call
          ( std::bind
            ( &async_function< Signature >::trigger< Args... >,
              this, std::forward< Args >( args )... ) ) );
}

template< typename Signature >
bool iscool::schedule::async_function< Signature >::empty() const
{
    return !_function;
}

template< typename Signature >
template< typename... Args >
void iscool::schedule::async_function< Signature >::trigger( Args... args )
{
    _connections.pop_front();
    _function( std::forward< Args >( args )... );
}

#endif
