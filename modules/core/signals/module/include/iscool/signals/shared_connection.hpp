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
#ifndef ISCOOL_SIGNALS_SHARED_CONNECTION_H
#define ISCOOL_SIGNALS_SHARED_CONNECTION_H

#include <iscool/signals/connection.hpp>
#include <iscool/signals/scoped_connection.hpp>

namespace iscool
{
  namespace signals
  {
    class shared_connection
    {
    private:
      typedef std::shared_ptr<scoped_connection> connection_pointer;

    public:
      shared_connection();
      shared_connection(const connection& c);
      ~shared_connection();

      bool connected() const;
      void disconnect();

      bool operator==(const shared_connection& that) const;
      bool operator!=(const shared_connection& that) const;

    private:
      connection_pointer _connection;
    };
  }
}

#endif
