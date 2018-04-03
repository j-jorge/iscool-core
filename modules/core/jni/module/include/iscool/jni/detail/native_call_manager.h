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
#ifndef ISCOOL_JNI_DETAIL_NATIVE_CALL_MANAGER_H
#define ISCOOL_JNI_DETAIL_NATIVE_CALL_MANAGER_H

#include "iscool/signals/scoped_connection.h"

#include "iscool/jni/java_ptr.h"
#include "iscool/jni/detail/native_callback.h"

#include <jni.h>

#include <boost/function/function_fwd.hpp>

#include <mutex>
#include <vector>

namespace iscool
{
    namespace jni
    {
        namespace detail
        {
            class native_call_manager
            {
            public:
                native_call_manager();
                ~native_call_manager();
            
                template< typename... Args >
                jlong register_callback
                ( native_callback_lifespan lifespan,
                  const boost::function< void( Args...) >& callback );

                void release_callback( jlong id );
                
                void call( jlong callback, jobjectArray arguments );

                native_call_manager( const native_call_manager& ) = delete;
                native_call_manager&
                operator=( const native_call_manager& ) = delete;
                
            private:
                struct native_call_data
                {
                    jlong callback;
                    java_ptr<jobjectArray> arguments;
                };
                
            private:
                void trigger_calls();

                void synchronous_call( native_call_data call );

                void schedule_trigger();
                void unschedule_trigger();

            private:
                std::vector< native_callback* > _callbacks;
                std::mutex _queue_access_mutex;
                std::vector< native_call_data > _queue;
                iscool::signals::scoped_connection _trigger_connection;
            };
        }
    }
}

#include "iscool/jni/detail/native_call_manager.tpp"

#endif
