// SPDX-License-Identifier: Apache-2.0#pragma once
#pragma once

#include <iscool/signals/identifier.hpp>
#include <iscool/signals/signal.hpp>

#define DETAIL_SIGNAL_FUNCTION_TYPE_NAME(NAME) NAME##_signal_function

#define DETAIL_SIGNAL_CONNECT_FUNCTION_NAME(NAME) connect_to_##NAME

#define DETAIL_DECLARE_SIGNAL(TYPE, NAME, MEMBER, TYPENAME)                   \
public:                                                                       \
  typedef TYPENAME ::iscool::signals::signal<TYPE>::slot_function_type        \
      DETAIL_SIGNAL_FUNCTION_TYPE_NAME(NAME);                                 \
                                                                              \
  ::iscool::signals::connection DETAIL_SIGNAL_CONNECT_FUNCTION_NAME(NAME)(    \
      DETAIL_SIGNAL_FUNCTION_TYPE_NAME(NAME) function) const;                 \
                                                                              \
private:                                                                      \
  DECLARE_SIGNAL_IDENTIFIER(TYPE, NAME)                                       \
  mutable iscool::signals::signal<TYPE,                                       \
                                  DETAIL_SIGNAL_IDENTIFIER_TYPE_NAME(NAME)>   \
      MEMBER;

#define DECLARE_SIGNAL(TYPE, NAME, MEMBER)                                    \
  DETAIL_DECLARE_SIGNAL(TYPE, NAME, MEMBER, )

#define DECLARE_SIGNAL_IN_TEMPLATE(TYPE, NAME, MEMBER)                        \
  DETAIL_DECLARE_SIGNAL(TYPE, NAME, MEMBER, typename)

#define DECLARE_VOID_SIGNAL(NAME, MEMBER) DECLARE_SIGNAL(void(), NAME, MEMBER)

#define DECLARE_SIGNAL_NO_MEMBER(TYPE, NAME)                                  \
public:                                                                       \
  typedef ::iscool::signals::signal<TYPE>::slot_function_type                 \
      DETAIL_SIGNAL_FUNCTION_TYPE_NAME(NAME);                                 \
                                                                              \
  ::iscool::signals::connection DETAIL_SIGNAL_CONNECT_FUNCTION_NAME(NAME)(    \
      DETAIL_SIGNAL_FUNCTION_TYPE_NAME(NAME) function) const;

#define DECLARE_VOID_SIGNAL_NO_MEMBER(NAME)                                   \
  DECLARE_SIGNAL_NO_MEMBER(void(), NAME)
