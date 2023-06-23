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
#ifndef WISHINGWELL_TPP
#define WISHINGWELL_TPP

template <typename T>
void iscool::wish::wishing_well::make_a_wish(const T& wish)
{
  _genie.grant<T>(wish);
}

template <typename T>
void iscool::wish::wishing_well::make_a_wish()
{
  _genie.grant<T>(T());
}

template <typename T>
bool iscool::wish::wishing_well::is_wish_grantable()
{
  return _genie.is_wish_valid<T>();
}

#endif
