// SPDX-License-Identifier: Apache-2.0
#pragma once

#define IMPLEMENT_JSON_CAST(T)                                                \
  namespace iscool::json                                                      \
  {                                                                           \
    template T cast<T>(const Json::Value&);                                   \
    template T cast<T>(const Json::Value&, const T&);                         \
    template T member_cast<T>(const Json::Value&, std::string_view);          \
  }\
