// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/memory/dynamic_pool.hpp>

namespace iscool::net
{
  class message;

  namespace detail
  {
    struct message_pool_traits
    {
      static bool clear(message&);
    };
  }

  using message_pool =
      iscool::memory::dynamic_pool<message, detail::message_pool_traits>;

}
