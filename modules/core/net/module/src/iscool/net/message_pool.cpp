// SPDX-License-Identifier: Apache-2.0
#include <iscool/net/message_pool.hpp>

#include <iscool/net/message/message.hpp>

bool iscool::net::detail::message_pool_traits::clear(message& m)
{
  // There's nothing to do, the user of the message has to call
  // message::reset() with the correct pameters.
  return true;
}
