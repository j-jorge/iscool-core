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
#ifndef ISCOOL_NET_SOCKET_STREAM_POOL_H
#define ISCOOL_NET_SOCKET_STREAM_POOL_H

#include <string>
#include <unordered_map>

namespace iscool
{
  namespace net
  {
    class socket_stream;

    class socket_stream_pool
    {
    public:
      socket_stream_pool();
      ~socket_stream_pool();

      socket_stream_pool(const socket_stream_pool&) = delete;
      socket_stream_pool& operator=(const socket_stream_pool&) = delete;

      socket_stream* get_for_host(const std::string& host);

    private:
      std::unordered_map<std::string, socket_stream*> _sockets;
    };
  }
}

#endif
