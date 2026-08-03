// SPDX-License-Identifier: Apache-2.0
#pragma once

namespace Json
{
  class Value;
}

namespace iscool::json
{
  template <typename T>
  T cast(const Json::Value& value);

  template <typename T>
  T cast(const Json::Value& value, const T& fallback);

  template <typename T>
  T member_cast(const Json::Value& value, std::string_view key);
}
