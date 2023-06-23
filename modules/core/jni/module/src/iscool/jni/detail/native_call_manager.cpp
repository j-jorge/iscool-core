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
#include <iscool/jni/detail/native_call_manager.hpp>

#include <iscool/jni/detail/get_jni_env.hpp>
#include <iscool/jni/native_callback_lifespan.hpp>
#include <iscool/schedule/delayed_call.hpp>

#include <mutex>

iscool::jni::detail::native_call_manager::native_call_manager()
{}

iscool::jni::detail::native_call_manager::~native_call_manager()
{
  unschedule_trigger();

  for (native_callback* pointer : _callbacks)
    {
      assert(pointer->get_lifespan() == native_callback_lifespan::one_shot);
      delete pointer;
    }
}

void iscool::jni::detail::native_call_manager::release_callback(jlong id)
{
#ifndef NDEBUG
  {
    std::unique_lock<std::mutex> lock(_queue_access_mutex);
    for (const auto& call : _queue)
      assert(call.callback != id);
  }
#endif

  native_callback* callback(
      reinterpret_cast<native_callback*>(std::intptr_t(id)));

  auto it(std::find(_callbacks.begin(), _callbacks.end(), callback));
  assert(it != _callbacks.end());

  _callbacks.erase(it);
}

void iscool::jni::detail::native_call_manager::call(jlong callback,
                                                    jobjectArray arguments)
{
  std::unique_lock<std::mutex> lock(_queue_access_mutex);
  schedule_trigger();
  native_call_data data;
  data.callback = callback;
  data.arguments = (jobjectArray)get_jni_env()->NewGlobalRef(arguments);
  _queue.push_back(data);
}

void iscool::jni::detail::native_call_manager::trigger_calls()
{
  std::vector<native_call_data> queue;
  {
    std::unique_lock<std::mutex> lock(_queue_access_mutex);
    std::swap(queue, _queue);
    unschedule_trigger();
  }

  for (const auto& call : queue)
    synchronous_call(call);
}

void iscool::jni::detail::native_call_manager::synchronous_call(
    native_call_data call)
{
  const std::intptr_t address(call.callback);

  native_callback* callback(reinterpret_cast<native_callback*>(address));

  const native_callback_lifespan lifespan(callback->get_lifespan());

  if (lifespan == native_callback_lifespan::persistent)
    {
      (*callback)(call.arguments);
      return;
    }

  assert(lifespan == native_callback_lifespan::one_shot);

  const std::vector<native_callback*>::iterator it(
      std::find(_callbacks.begin(), _callbacks.end(), callback));

  assert(it != _callbacks.end());
  _callbacks.erase(it);

  std::unique_ptr<native_callback> callback_pointer(callback);
  (*callback_pointer)(call.arguments);
}

void iscool::jni::detail::native_call_manager::schedule_trigger()
{
  if (_trigger_connection.connected())
    return;

  _trigger_connection = schedule::delayed_call(
      std::bind(&native_call_manager::trigger_calls, this));
}

void iscool::jni::detail::native_call_manager::unschedule_trigger()
{
  _trigger_connection.disconnect();
}
