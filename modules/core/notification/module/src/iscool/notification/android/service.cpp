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
#include <iscool/notification/android/service.hpp>

#include <iscool/jni/get_static_method.hpp>
#include <iscool/jni/new_java_string.hpp>
#include <iscool/jni/static_method_jboolean.hpp>
#include <iscool/jni/static_method_void.hpp>

void iscool::notification::android::service::enable_notifications()
{}

bool iscool::notification::android::service::are_notifications_enabled() const
{
  const jni::static_method<jboolean> method(jni::get_static_method<jboolean>(
      "iscool/notification/NotificationService", "areNotificationsEnabled",
      "()Z"));

  return method();
}

void iscool::notification::android::service::schedule(
    std::size_t id, const std::chrono::seconds& delay,
    const std::string& title, const std::string& message)
{
  const jni::static_method<void> method(jni::get_static_method<void>(
      "iscool/notification/NotificationService", "schedule",
      "(IJLjava/lang/String;Ljava/lang/String;)V"));

  method(id, delay.count(), iscool::jni::new_java_string(title),
         iscool::jni::new_java_string(message));
}

void iscool::notification::android::service::cancel_all()
{
  const jni::static_method<void> method(jni::get_static_method<void>(
      "iscool/notification/NotificationService", "cancelAll", "()V"));

  method();
}
