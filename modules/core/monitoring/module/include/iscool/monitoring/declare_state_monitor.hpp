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
#ifndef ISCOOL_MONITORING_DECLARE_STATE_MONITOR_H
#define ISCOOL_MONITORING_DECLARE_STATE_MONITOR_H

#include <iscool/memory/pimpl.hpp>

#define ic_declare_state_monitor(field_name)                                  \
  class state_monitor_##field_name;                                           \
                                                                              \
  iscool::memory::pimpl<state_monitor_##field_name, sizeof(char)> field_name

#endif
