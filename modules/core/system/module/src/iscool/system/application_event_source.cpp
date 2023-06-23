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
#include "iscool/system/application_event_source.h"

#include "iscool/signals/implement_signal.h"

IMPLEMENT_SIGNAL(iscool::system::application_event_source, enter_background,
                 _enter_background);
IMPLEMENT_SIGNAL(iscool::system::application_event_source, enter_foreground,
                 _enter_foreground);

iscool::system::application_event_source::application_event_source() = default;
iscool::system::application_event_source::~application_event_source() =
    default;

void iscool::system::application_event_source::dispatch_enter_background()
    const
{
  _enter_background();
}

void iscool::system::application_event_source::dispatch_enter_foreground()
    const
{
  _enter_foreground();
}
