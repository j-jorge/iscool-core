// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/net/endpoint.hpp>
#include <iscool/net/socket_mode.hpp>

#include <iscool/memory/dynamic_pool.hpp>
#include <iscool/signals/declare_signal.hpp>

#include <boost/asio/io_context.hpp>

#include <atomic>
#include <cstdint>
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

      std::uint64_t sent_bytes() const;
      std::uint64_t received_bytes() const;

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

      std::atomic<std::uint64_t> _sent_bytes;
      std::atomic<std::uint64_t> _received_bytes;
    };
  }
}
