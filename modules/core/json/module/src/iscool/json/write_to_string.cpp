// SPDX-License-Identifier: Apache-2.0
#include <iscool/json/write_to_string.hpp>

#include <iscool/json/write_to_stream.hpp>

#include <sstream>

bool iscool::json::write_to_string(std::string& output,
                                   const Json::Value& value)
{
  std::ostringstream oss(std::move(output));

  const bool r = write_to_stream(oss, value);

  output = std::move(oss).str();

  return r;
}
