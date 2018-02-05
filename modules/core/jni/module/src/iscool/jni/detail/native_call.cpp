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
#include "iscool/jni/detail/native_call.h"

#include "iscool/jni/detail/native_call_manager.h"

namespace iscool
{
    namespace jni
    {
        namespace detail
        {
            static native_call_manager* manager( nullptr );
        }
    }
}

void iscool::jni::detail::initialize_native_calls()
{
    assert( detail::manager == nullptr );
    detail::manager = new detail::native_call_manager();
}

void iscool::jni::detail::finalize_native_calls()
{
    assert( detail::manager != nullptr );
    delete detail::manager;
    detail::manager = nullptr;
}

iscool::jni::detail::native_call_manager&
iscool::jni::detail::get_native_call_manager()
{
    assert( detail::manager != nullptr );
    return *detail::manager;
}

extern "C" void Java_iscool_jni_NativeCall_call
( JNIEnv* env, jlong callback, jobjectArray arguments )
{
    iscool::jni::detail::get_native_call_manager().call( callback, arguments );
}
