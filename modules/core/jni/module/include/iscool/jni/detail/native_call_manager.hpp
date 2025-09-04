// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/jni/detail/native_callback.hpp>
#include <iscool/jni/java_ptr.hpp>

#include <iscool/schedule/scoped_connection.hpp>

#include <jni.h>

#include <functional>
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

        template <typename... Args>
        jlong register_callback(native_callback_lifespan lifespan,
                                const std::function<void(Args...)>& callback);

        void release_callback(jlong id);

        void call(jlong callback, jobjectArray arguments);

        native_call_manager(const native_call_manager&) = delete;
        native_call_manager& operator=(const native_call_manager&) = delete;

      private:
        struct native_call_data
        {
          jlong callback;
          java_ptr<jobjectArray> arguments;
        };

      private:
        void trigger_calls();

        void synchronous_call(native_call_data call);

        void schedule_trigger();
        void unschedule_trigger();

      private:
        std::vector<native_callback*> _callbacks;
        std::mutex _queue_access_mutex;
        std::vector<native_call_data> _queue;
        iscool::schedule::scoped_connection _trigger_connection;
      };
    }
  }
}

#include <iscool/jni/detail/native_call_manager.tpp>
