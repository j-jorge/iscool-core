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
#include <iscool/social/android/link_service.hpp>

#include <iscool/jni/get_static_method.hpp>
#include <iscool/jni/static_method_void.hpp>
#include <iscool/jni/string_bytes.hpp>

void iscool::social::android::link_service::open_in_facebook(
    const std::string& page)
{
  const jni::static_method<void> method(jni::get_static_method<void>(
      "iscool/social/LinkService", "openInFacebook", "([B)V"));

  method(jni::string_bytes(page));
}

void iscool::social::android::link_service::open_in_twitter(
    const std::string& page)
{
  const jni::static_method<void> method(jni::get_static_method<void>(
      "iscool/social/LinkService", "openInTwitter", "([B)V"));

  method(jni::string_bytes(page));
}
