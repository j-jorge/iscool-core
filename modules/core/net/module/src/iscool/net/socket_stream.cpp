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
#include <iscool/net/socket_stream.hpp>

#include <iscool/schedule/delayed_call.hpp>
#include <iscool/signals/implement_signal.hpp>

IMPLEMENT_SIGNAL(iscool::net::socket_stream, received, _received);

iscool::net::socket_stream::socket_stream() = default;

iscool::net::socket_stream::socket_stream(const std::string& host,
                                          socket_mode::client)
{
  connect(host);
}

iscool::net::socket_stream::socket_stream(const std::string& host,
                                          socket_mode::server)
{
  listen(host);
}

iscool::net::socket_stream::socket_stream(unsigned short port)
{
  listen(port);
}

iscool::net::socket_stream::~socket_stream()
{
  stop();
}

void iscool::net::socket_stream::connect(const std::string& host)
{
  stop();
  _socket.reset(new iscool::net::detail::socket(host, socket_mode::client{}));
  start();
}

void iscool::net::socket_stream::listen(const std::string& host)
{
  stop();
  _socket.reset(new iscool::net::detail::socket(host, socket_mode::server{}));
  start();
}

void iscool::net::socket_stream::listen(unsigned short port)
{
  stop();
  _socket.reset(new iscool::net::detail::socket(port));
  start();
}

void iscool::net::socket_stream::send(const iscool::net::byte_array& bytes)
{
  _socket->send(bytes);
}

void iscool::net::socket_stream::send(const endpoint& target,
                                      const iscool::net::byte_array& bytes)
{
  _socket->send(target, bytes);
}

void iscool::net::socket_stream::start()
{
  _received_connection = _socket->connect_to_received(
      [this](const endpoint& e, std::size_t id, const byte_array& b) -> void
      {
        queue_bytes(e, id, b);
      });

  _update_thread = std::thread(
      [this]() -> void
      {
        _socket->run();
      });
}

void iscool::net::socket_stream::stop()
{
  if (!_socket)
    return;

  _socket->close();

  {
    const std::unique_lock<std::mutex> lock(_queue_access_mutex);
    _dispatch_connection.disconnect();
    _received_connection.disconnect();
  }

  _update_thread.join();
}

void iscool::net::socket_stream::queue_bytes(const endpoint& target,
                                             std::size_t id,
                                             const byte_array& bytes)
{
  const std::unique_lock<std::mutex> lock(_queue_access_mutex);
  _main_bytes_queue.push_back(queued_bytes{ target, id, &bytes });

  if (_dispatch_connection.connected())
    return;

  assert(!_dispatch_connection.connected());

  _dispatch_connection = iscool::schedule::delayed_call(
      [this]() -> void
      {
        dispatch_bytes();
      });
}

void iscool::net::socket_stream::dispatch_bytes()
{
  {
    const std::unique_lock<std::mutex> lock(_queue_access_mutex);

    _tmp_bytes_queue.swap(_main_bytes_queue);
    _main_bytes_queue.clear();
  }

  for (const bytes_queue::value_type& entry : _tmp_bytes_queue)
    _received(entry.target, *entry.bytes);

  for (const bytes_queue::value_type& entry : _tmp_bytes_queue)
    _socket->recycle_buffer(entry.id);
}
