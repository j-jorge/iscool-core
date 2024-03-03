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
#ifndef ISCOOL_NET_SOCKET_STREAM_H
#define ISCOOL_NET_SOCKET_STREAM_H

#include <iscool/net/byte_array.hpp>
#include <iscool/net/detail/socket.hpp>
#include <iscool/net/socket_mode.hpp>
#include <iscool/signals/declare_signal.hpp>

#include <mutex>
#include <thread>

namespace iscool
{
  namespace net
  {
    class socket_stream
    {
    public:
      DECLARE_SIGNAL(void(const endpoint&, const iscool::net::byte_array&),
                     received, _received);

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
        byte_array bytes;
      };

      typedef std::vector<queued_bytes> bytes_queue;

    private:
      void start();
      void stop();

      void queue_bytes(const endpoint& target, const byte_array& bytes);
      void dispatch_bytes();

    private:
      std::unique_ptr<iscool::net::detail::socket> _socket;

      bytes_queue _bytes_queue;
      std::mutex _queue_access_mutex;
      std::thread _update_thread;

      iscool::signals::connection _dispatch_connection;
    };
  }
}

#endif
