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
#include "iscool/net/socket_stream_pool.h"

#include "iscool/net/log_context.h"

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"
#include "iscool/net/socket_stream.h"

#include <cassert>

iscool::net::socket_stream_pool::socket_stream_pool() = default;

iscool::net::socket_stream_pool::~socket_stream_pool()
{
    for ( const auto& e : _sockets )
        delete e.second;
}

iscool::net::socket_stream*
iscool::net::socket_stream_pool::get_for_host( const std::string& host )
{
    const auto it( _sockets.find( host ) );

    if ( it != _sockets.end() )
        return it->second;

    socket_stream* result( nullptr );

    try
    {
        result = new socket_stream( host, socket_mode::client{} );
    }
    catch( const boost::system::system_error& e )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "could not create the socket for host '%s': %s", host, e.what() );
        return nullptr;
    }

    assert( result != nullptr );
    _sockets[ host ] = result;
    return result;
}
