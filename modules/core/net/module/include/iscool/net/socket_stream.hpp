// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/net/byte_array.hpp>
#include <iscool/net/detail/socket.hpp>
#include <iscool/net/socket_mode.hpp>
#include <iscool/schedule/connection.hpp>
#include <iscool/signals/declare_signal.hpp>

#include <mutex>
#include <thread>

namespace iscool::net
{
  class socket_stream
  {
  public:
    DECLARE_SIGNAL(void(const endpoint&, const byte_array&), received,
                   _received)

  public:
    socket_stream();

    socket_stream(const socket_stream&) = delete;
    socket_stream(socket_stream&&) = delete;

    socket_stream& operator=(const socket_stream&) = delete;
    socket_stream& operator=(socket_stream&&) = delete;

    /**
     * Open a socket with the given remote host. This kind of socket can
     * send with no explicit end point.
     */
    socket_stream(const std::string& host, socket_mode::client);

    /**
     * Open a socket locally. The remote endpoint must be explicited
     * with every send.
     */
    socket_stream(const std::string& host, socket_mode::server);

    /**
     * Open a socket in server mode, locally on the given port. The
     * remote endpoint must be explicited with every send.
     */
    explicit socket_stream(unsigned short port);

    /**
     * Open a socket with the given remote host. This kind of socket can
     * send with no explicit end point.
     */
    void connect(const std::string& host);

    /**
     * Open a socket locally. The remote endpoint must be explicited
     * with every send.
     */
    void listen(const std::string& host);

    /**
     * Open a socket in server mode, locally on the given port. The
     * remote endpoint must be explicited with every send.
     */
    void listen(unsigned short port);

    ~socket_stream();

    void send(const iscool::net::byte_array& bytes);
    void send(const endpoint& target, const iscool::net::byte_array& bytes);

  private:
    struct queued_bytes
    {
      endpoint target;
      std::size_t id;
      const byte_array* bytes;
    };

    typedef std::vector<queued_bytes> bytes_queue;

  private:
    void start();
    void stop();

    void queue_bytes(const endpoint& target, std::size_t id,
                     const byte_array& bytes);
    void dispatch_bytes();

  private:
    std::unique_ptr<iscool::net::detail::socket> _socket;

    bytes_queue _main_bytes_queue;
    bytes_queue _tmp_bytes_queue;
    std::mutex _queue_access_mutex;
    std::thread _update_thread;

    iscool::signals::connection _received_connection;
    iscool::schedule::connection _dispatch_connection;
  };
}
