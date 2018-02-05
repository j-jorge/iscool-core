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
#include "iscool/net/detail/socket.h"

#include "iscool/net/log_context.h"

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"
#include "iscool/log/nature/info.h"
#include "iscool/net/byte_array.h"
#include "iscool/signals/implement_signal.h"

#include <boost/bind.hpp>

IMPLEMENT_SIGNAL( iscool::net::detail::socket, received, _received );

iscool::net::detail::socket::socket( const std::string& host )
    : _work( _io_service )
{
    initialize_remote_endpoint( host );
    receive();
}

void iscool::net::detail::socket::run()
{
    _io_service.run();
}

void iscool::net::detail::socket::close()
{
    _io_service.stop();
}

void iscool::net::detail::socket::send( const byte_array& bytes )
{
    send( _send_endpoint, bytes );
}

void iscool::net::detail::socket::send
( const endpoint& endpoint, const byte_array& bytes )
{
    bool call_receive( false );

    if ( _socket == nullptr )
    {
        allocate_socket();
        call_receive = true;
    }

    try
    {
        send_bytes_no_error_check( endpoint, bytes );

        if ( call_receive )
            receive();
    }
    catch( const std::exception& e )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "the data could not be sent: %s", e.what() );
    }
}

void iscool::net::detail::socket::allocate_socket()
{
    assert( _socket == nullptr );
    
    _socket.reset( new boost::asio::ip::udp::socket( _io_service ) );
    _socket->open( _send_endpoint.protocol() );
}

void iscool::net::detail::socket::initialize_remote_endpoint
( const std::string& host )
{
    ic_causeless_log
        ( iscool::log::nature::info(), log_context(),
          "connecting to '%s'", host );

    const std::string::size_type colon( host.find_first_of( ':' ) );

    if ( colon == std::string::npos )
        throw std::runtime_error( "missing colon in host address." );

    initialize_remote_endpoint
        ( host.substr( 0, colon ), host.substr( colon + 1 ) );
}

void
iscool::net::detail::socket::initialize_remote_endpoint
( const std::string& address, const std::string& port )
{
    boost::asio::ip::udp::resolver resolver( _io_service );
    boost::asio::ip::udp::resolver::query query
        ( address, port );
    _send_endpoint = *resolver.resolve( query );
}

void
iscool::net::detail::socket::send_bytes_no_error_check
( const endpoint& endpoint, const byte_array& bytes )
{
    std::shared_ptr< byte_array > raw( new byte_array( bytes ) );
    boost::asio::const_buffer buffer( & *raw->begin(), raw->size() );

    _socket->async_send_to
        ( boost::asio::buffer( buffer ), endpoint,
          boost::bind( &socket::bytes_sent, this, raw, _1, _2 ) );
}

void iscool::net::detail::socket::bytes_sent
( const std::shared_ptr< byte_array >& bytes,
  const boost::system::error_code& error, std::size_t bytes_transferred )
{
    if ( error )
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "the data could not be sent: %s", error.message() );
}

void iscool::net::detail::socket::receive()
{
    if ( _socket == nullptr )
        allocate_socket();

    _socket->async_receive_from
        ( boost::asio::null_buffers(), _receive_endpoint,
          boost::bind( &socket::bytes_received, this, _1 ) );
}

void iscool::net::detail::socket::bytes_received
( const boost::system::error_code& error )
{
    if ( error )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "the data could not be received: %s", error.message() );
        return;
    }

    if ( read_available_bytes() )
        receive();
}

bool iscool::net::detail::socket::read_available_bytes()
{
    boost::mutex::scoped_lock lock( _receive_bytes );

    const std::size_t available( _socket->available() );
    const std::unique_ptr< std::uint8_t[] > buffer
        ( new std::uint8_t[ available ] );
    std::size_t bytes_transferred( 0 );
    
    try
    {
        bytes_transferred =
            _socket->receive_from
            ( boost::asio::buffer( buffer.get(), available ),
              _receive_endpoint );
    }
    catch ( const std::exception& e )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "could not read from socket: %s", e.what() );
        _socket = nullptr;
        return false;
    }

    dispatch_bytes( buffer.get(), bytes_transferred );
    return true;
}

void iscool::net::detail::socket::dispatch_bytes
( std::uint8_t* buffer, std::size_t bytes_transferred ) const
{
    const byte_array bytes( buffer, buffer + bytes_transferred );
    _received( _receive_endpoint, bytes );
}
