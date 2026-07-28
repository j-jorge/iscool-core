// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/send_function.hpp>

namespace iscool::http
{
  void initialize(send_function delegate);
  void finalize();

  class scoped_http_delegate
  {
  public:
    explicit scoped_http_delegate(send_function delegate);
    scoped_http_delegate(const scoped_http_delegate&) = delete;
    ~scoped_http_delegate();

    scoped_http_delegate& operator=(const scoped_http_delegate&) = delete;
  };
}
