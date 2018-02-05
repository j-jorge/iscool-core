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
#ifndef ISCOOL_PREFERENCES_STORE_TPP
#define ISCOOL_PREFERENCES_STORE_TPP

#include "iscool/preferences/property_map.impl.h"

template< typename Rep, typename Period >
iscool::preferences::store::store
( const std::chrono::duration< Rep, Period >& flush_delay,
  const property_map& initial_values,
  const save_function& save_delegate )
    : _flush_delay( flush_delay ),
      _preferences( initial_values ),
      _save_delegate( save_delegate )
{

}

template< typename T >
void
iscool::preferences::store::set_value( const std::string& key, const T& value )
{
    const iscool::optional< T > old_value( _preferences.get< T >( key ) );

    if ( old_value && ( *old_value == value ) )
        return;
                
    _dirty.set( key, value );
    _preferences.set( key, value );
    schedule_save();
}

template< typename T >
T iscool::preferences::store::get_value
( const std::string& key, const T& default_value ) const
{
    const iscool::optional< T > result( _preferences.get< T >( key ) );

    if ( result )
        return *result;

    return default_value;
}

#endif

