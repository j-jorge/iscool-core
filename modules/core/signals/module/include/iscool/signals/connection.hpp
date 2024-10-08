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
#ifndef ISCOOL_SIGNALS_CONNECTION_H
#define ISCOOL_SIGNALS_CONNECTION_H

#include <iscool/signals/detail/slot.hpp>

#include <memory>

namespace iscool
{
  namespace signals
  {
    class connection
    {
    public:
      connection();
      explicit connection(const std::weak_ptr<detail::slot>& slot);
      connection(const connection& that);
      connection(connection&& that);
      ~connection();

      connection& operator=(const connection& that);
      connection& operator=(connection&& that);

      bool operator==(const connection& that) const;
      bool operator!=(const connection& that) const;

      bool connected() const;
      void disconnect() const;

    private:
      std::weak_ptr<detail::slot> _slot;
    };
  }
}

#endif
