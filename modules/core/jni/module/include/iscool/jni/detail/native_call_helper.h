/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#ifndef ISCOOL_JNI_DETAIL_NATIVE_CALL_HELPER_H
#define ISCOOL_JNI_DETAIL_NATIVE_CALL_HELPER_H

#include "iscool/meta/indices.h"

#include <functional>
#include <tuple>

namespace iscool
{
    namespace jni
    {
        namespace detail
        {
            template< typename T, typename U >
            struct native_call_helper;

            template< typename... Arg, std::size_t... I >
            struct native_call_helper
            <
                std::tuple< Arg... >,
                meta::indices< I... >
            >
            {
                static void call
                ( const std::function< void( Arg... ) >& f,
                  const java_ptr< jobjectArray >& arguments );
            };
        }
    }
}

#include "iscool/jni/detail/native_call_helper.tpp"

#endif
