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
#ifndef ISCOOL_NET_SOCKET_H
#define ISCOOL_NET_SOCKET_H

#include "iscool/net/endpoint.h"
#include "iscool/net/socket_mode.h"
#include "iscool/signals/declare_signal.h"

#include <boost/asio/io_service.hpp>

#include <mutex>

namespace iscool
{
    namespace net
    {
        class byte_array;

        namespace detail
        {
            class socket
            {
            public:
                DECLARE_SIGNAL
                ( void( const endpoint&, const byte_array& ), received,
                  _received );

            public:
                /**
                 * Open a socket with the given remote host. This kind of socket
                 * can send with no explicit end point.
                 */
                socket( const std::string& host, socket_mode::client );

                /**
                 * Open a socket locally. The remote endpoint must be explicited
                 * with every send.
                 */
                socket( const std::string& host, socket_mode::server );

                /**
                 * Open a socket in server mode, locally on the given port. The
                 * remote endpoint must be explicited with every send.
                 */
                explicit socket( unsigned short port );

                void run();
                void close();

                void send( const byte_array& bytes );
                void send( const endpoint& endpoint, const byte_array& bytes );

            private:
                using socket_pointer =
                    std::unique_ptr< boost::asio::ip::udp::socket >;
                using socket_allocator = void (socket::*)();

            private:
                void allocate_client_socket();
                void allocate_server_socket();

                endpoint build_endpoint( const std::string& host );
                endpoint build_endpoint
                ( const std::string& address, const std::string& port );

                void send_bytes_no_error_check
                ( const endpoint& endpoint, const byte_array& bytes );
                void bytes_sent
                ( const std::shared_ptr< byte_array >& bytes,
                  const boost::system::error_code& error,
                  std::size_t bytes_transferred );

                void receive();
                void bytes_received( const boost::system::error_code& error );

                bool read_available_bytes();
                void dispatch_bytes
                ( std::uint8_t* buffer, std::size_t bytes_transferred ) const;

            private:
                boost::asio::io_service _io_service;
                boost::asio::io_service::work _work;
                endpoint _send_endpoint;
                endpoint _receive_endpoint;
                const socket_allocator _allocate_socket;
                socket_pointer _socket;

                std::mutex _receive_bytes;
            };
        }
    }
}

#endif
