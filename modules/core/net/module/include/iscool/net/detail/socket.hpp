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
#pragma once

#include <iscool/net/endpoint.hpp>
#include <iscool/net/socket_mode.hpp>

#include <iscool/memory/dynamic_pool.hpp>
#include <iscool/signals/declare_signal.hpp>

#include <boost/asio/io_context.hpp>

#include <mutex>

namespace iscool::net
{
  class byte_array;

  namespace detail
  {
    class socket
    {
    public:
      DECLARE_SIGNAL(void(const endpoint&, std::size_t, const byte_array&),
                     received, _received)

    public:
      /**
       * Open a socket with the given remote host. This kind of socket
       * can send with no explicit end point.
       */
      socket(std::string_view host, socket_mode::client);

      /**
       * Open a socket locally. The remote endpoint must be explicited
       * with every send.
       */
      socket(std::string_view host, socket_mode::server);

      /**
       * Open a socket in server mode, locally on the given port. The
       * remote endpoint must be explicited with every send.
       */
      explicit socket(unsigned short port);

      void run();
      void close();

      void send(const byte_array& bytes);
      void send(const endpoint& endpoint, const byte_array& bytes);

      void recycle_buffer(std::size_t id);

    private:
      using socket_pointer = std::unique_ptr<boost::asio::ip::udp::socket>;
      using socket_allocator = void (socket::*)();

      struct byte_array_pool_traits
      {
        static bool clear(byte_array& b);
      };

      using buffer_pool =
          iscool::memory::dynamic_pool<byte_array, byte_array_pool_traits>;

    private:
      void allocate_client_socket();
      void allocate_server_socket();

      endpoint build_endpoint(std::string_view host);
      endpoint build_endpoint(std::string_view address, std::string_view port);

      void send_bytes_no_error_check(const endpoint& endpoint,
                                     const byte_array& bytes);
      void bytes_sent(const boost::system::error_code& error,
                      std::size_t bytes_transferred);

      void receive();
      void bytes_received(const boost::system::error_code& error);

      bool read_available_bytes();
      void dispatch_bytes(std::size_t id, const byte_array& bytes) const;

    private:
      boost::asio::io_context _io_context;
      const boost::asio::executor_work_guard<
          boost::asio::io_context::executor_type>
          _work;

      endpoint _send_endpoint;
      endpoint _receive_endpoint;
      const socket_allocator _allocate_socket;
      socket_pointer _socket;

      std::mutex _receive_bytes;

      buffer_pool _buffers;
    };
  }
}
