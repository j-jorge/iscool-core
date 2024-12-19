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
#include <iscool/net/detail/socket.hpp>

#include <iscool/net/log_context.hpp>

#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>
#include <iscool/log/nature/info.hpp>
#include <iscool/net/byte_array.hpp>
#include <iscool/signals/implement_signal.hpp>

IMPLEMENT_SIGNAL(iscool::net::detail::socket, received, _received);

iscool::net::detail::socket::socket(std::string_view host, socket_mode::client)
  : _work(_io_context.get_executor())
  , _send_endpoint(build_endpoint(host))
  , _allocate_socket(&socket::allocate_client_socket)
{
  receive();
}

iscool::net::detail::socket::socket(std::string_view host, socket_mode::server)
  : _work(_io_context.get_executor())
  , _receive_endpoint(build_endpoint(host))
  , _allocate_socket(&socket::allocate_server_socket)
{
  receive();
}

iscool::net::detail::socket::socket(unsigned short port)
  : _work(_io_context.get_executor())
  , _receive_endpoint(build_endpoint("0.0.0.0", std::to_string(port)))
  , _allocate_socket(&socket::allocate_server_socket)
{
  receive();
}

void iscool::net::detail::socket::run()
{
  _io_context.run();
}

void iscool::net::detail::socket::close()
{
  _io_context.stop();
}

void iscool::net::detail::socket::send(const byte_array& bytes)
{
  send(_send_endpoint, bytes);
}

void iscool::net::detail::socket::send(const endpoint& endpoint,
                                       const byte_array& bytes)
{
  bool call_receive(false);

  if (_socket == nullptr)
    {
      (this->*_allocate_socket)();
      call_receive = true;
    }

  try
    {
      send_bytes_no_error_check(endpoint, bytes);

      if (call_receive)
        receive();
    }
  catch (const std::exception& e)
    {
      ic_log(iscool::log::nature::error(), log_context(),
             "the data could not be sent: {}", e.what());
    }
}

void iscool::net::detail::socket::allocate_client_socket()
{
  assert(_socket == nullptr);

  _socket.reset(new boost::asio::ip::udp::socket(_io_context,
                                                 _send_endpoint.protocol()));
}

void iscool::net::detail::socket::allocate_server_socket()
{
  assert(_socket == nullptr);

  _socket.reset(
      new boost::asio::ip::udp::socket(_io_context, _receive_endpoint));
}

iscool::net::endpoint
iscool::net::detail::socket::build_endpoint(std::string_view host)
{
  ic_log(iscool::log::nature::info(), log_context(), "connecting to '{}'",
         host);

  const std::string::size_type colon(host.find_first_of(':'));

  if (colon == std::string::npos)
    throw std::runtime_error("missing colon in host address.");

  return build_endpoint(host.substr(0, colon), host.substr(colon + 1));
}

iscool::net::endpoint
iscool::net::detail::socket::build_endpoint(std::string_view address,
                                            std::string_view port)
{
  boost::asio::ip::udp::resolver resolver(_io_context);
  return *resolver.resolve(boost::asio::ip::udp::v4(), address, port).begin();
}

void iscool::net::detail::socket::send_bytes_no_error_check(
    const endpoint& endpoint, const byte_array& bytes)
{
  std::shared_ptr<byte_array> raw(new byte_array(bytes));
  boost::asio::const_buffer buffer(&*raw->begin(), raw->size());

  _socket->async_send_to(boost::asio::buffer(buffer), endpoint,
                         std::bind(&socket::bytes_sent, this, raw,
                                   std::placeholders::_1,
                                   std::placeholders::_2));
}

void iscool::net::detail::socket::bytes_sent(
    const std::shared_ptr<byte_array>& bytes,
    const boost::system::error_code& error, std::size_t bytes_transferred)
{
  if (error)
    ic_log(iscool::log::nature::error(), log_context(),
           "the data could not be sent: {}", error.message());
}

void iscool::net::detail::socket::receive()
{
  if (_socket == nullptr)
    (this->*_allocate_socket)();

  _socket->async_receive_from(
      boost::asio::null_buffers(), _receive_endpoint,
      std::bind(&socket::bytes_received, this, std::placeholders::_1));
}

void iscool::net::detail::socket::bytes_received(
    const boost::system::error_code& error)
{
  if (error)
    {
      ic_log(iscool::log::nature::error(), log_context(),
             "the data could not be received: {}", error.message());
      return;
    }

  if (read_available_bytes())
    receive();
}

bool iscool::net::detail::socket::read_available_bytes()
{
  std::unique_lock<std::mutex> lock(_receive_bytes);

  const std::size_t available(_socket->available());
  const std::unique_ptr<std::uint8_t[]> buffer(new std::uint8_t[available]);
  std::size_t bytes_transferred(0);

  try
    {
      bytes_transferred = _socket->receive_from(
          boost::asio::buffer(buffer.get(), available), _receive_endpoint);
    }
  catch (const std::exception& e)
    {
      ic_log(iscool::log::nature::error(), log_context(),
             "could not read from socket: {}", e.what());
      _socket = nullptr;
      return false;
    }

  dispatch_bytes(buffer.get(), bytes_transferred);
  return true;
}

void iscool::net::detail::socket::dispatch_bytes(
    std::uint8_t* buffer, std::size_t bytes_transferred) const
{
  const byte_array bytes(buffer, buffer + bytes_transferred);
  _received(_receive_endpoint, bytes);
}
