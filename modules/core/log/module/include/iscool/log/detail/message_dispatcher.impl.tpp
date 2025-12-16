// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iterator>

template <typename... Args>
void iscool::log::detail::message_dispatcher::dispatch(
    const nature::nature& nature, const context& context,
    std::format_string<Args...> pattern, Args&&... args)
{
  const std::unique_lock lock(_mutex);

  _message.clear();
  std::vformat_to(std::back_inserter(_message), pattern.get(),
                  std::make_format_args(args...));
  dispatch_to_delegates(nature, context, _message);
}
