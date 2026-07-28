// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/setup.hpp>

#include <iscool/http/detail/get_service_statistics.hpp>
#include <iscool/http/detail/send_delegate.hpp>
#include <iscool/http/detail/service_statistics.hpp>

void iscool::http::initialize(send_function delegate)
{
  assert(delegate);
  assert(!detail::send_delegate);
  detail::send_delegate = std::move(delegate);
  detail::get_service_statistics().reset();
}

void iscool::http::finalize()
{
  detail::send_delegate = send_function();
}

iscool::http::scoped_http_delegate::scoped_http_delegate(
    send_function delegate)
{
  initialize(std::move(delegate));
}

iscool::http::scoped_http_delegate::~scoped_http_delegate()
{
  finalize();
}
