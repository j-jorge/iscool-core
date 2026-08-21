// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/http/request_connection.hpp>

bool iscool::http::request_connection::connected() const
{
  return result.connected() || error.connected();
}

void iscool::http::request_connection::disconnect()
{
  result.disconnect();
  error.disconnect();
}
