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
#include "iscool/jni/setup.h"

#include "iscool/jni/detail/get_jni_env.h"
#include "iscool/jni/detail/native_call.h"

void iscool::jni::initialize( environment_delegate delegate )
{
    assert( detail::get_jni_env.empty() );
    assert( !delegate.empty() );
    
    detail::get_jni_env = delegate;
    detail::initialize_native_calls();
}

void iscool::jni::finalize()
{
    detail::finalize_native_calls();
    detail::get_jni_env = environment_delegate();
}
