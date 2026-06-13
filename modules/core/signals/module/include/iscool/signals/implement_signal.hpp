// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/signals/declare_signal.hpp>
#include <iscool/signals/signal.impl.tpp>

#include <boost/preprocessor/punctuation/remove_parens.hpp>

#include <utility>

#define DETAIL_IMPLEMENT_SIGNAL(SCOPE, NAME, MEMBER, TYPENAME)                \
  ::iscool::signals::connection                                               \
  BOOST_PP_REMOVE_PARENS(SCOPE)::DETAIL_SIGNAL_CONNECT_FUNCTION_NAME(NAME)(   \
      DETAIL_SIGNAL_FUNCTION_TYPE_NAME(NAME) function) const                  \
  {                                                                           \
    return MEMBER.connect(std::move(function));                               \
  }

#define IMPLEMENT_SIGNAL(SCOPE, NAME, MEMBER)                                 \
  DETAIL_IMPLEMENT_SIGNAL(SCOPE, NAME, MEMBER, )

#define IMPLEMENT_SIGNAL_IN_TEMPLATE(SCOPE, NAME, MEMBER)                     \
  DETAIL_IMPLEMENT_SIGNAL(SCOPE, NAME, MEMBER, typename)
