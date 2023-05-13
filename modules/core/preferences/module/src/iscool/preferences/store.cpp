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
#include "iscool/preferences/store.h"

#include "iscool/preferences/property_map.impl.h"
#include "iscool/schedule/delayed_call.h"


#include <algorithm>
#include <cassert>

namespace iscool
{
    namespace preferences
    {
        namespace detail
        {
            class copy_new_fields
            {
            public:
                explicit copy_new_fields( property_map& target );
                
                template< typename T >
                void operator()( const std::string& key, const T& value );

            private:
                property_map& _target;
            };
            
            class collect_keys
            {
            public:
                explicit collect_keys( std::vector< std::string >& keys );
                
                template< typename T >
                void operator()( std::string key, T&& );

            private:
                std::vector< std::string >& _keys;
            };
        }
    }
}

iscool::preferences::store::store
( const std::chrono::milliseconds& flush_delay,
  const property_map& initial_values,
  const save_function& save_delegate )
    : _flush_delay( flush_delay ),
      _preferences( initial_values ),
      _save_delegate( save_delegate )
{

}

bool iscool::preferences::store::is_dirty() const
{
    return !_pending_changes.empty() || !_dirty.empty();
}

void iscool::preferences::store::flush()
{
    assert( is_dirty() );
    
    if ( !_pending_changes.empty() )
        abort_save();

    assert( !_dirty.empty() );
    save();
}

void iscool::preferences::store::confirm_save()
{
    assert( !_pending_changes.empty() );
    
    _pending_changes.clear();
    schedule_save();
}

void iscool::preferences::store::save_error()
{
    assert( !_pending_changes.empty() );

    abort_save();
    schedule_save();
}

std::vector< std::string > iscool::preferences::store::get_keys() const
{
    std::vector< std::string > result;
    detail::collect_keys visitor( result );

    _preferences.visit( visitor );
    _pending_changes.visit( visitor );
    _dirty.visit( visitor );
    
    return result;
}

const iscool::preferences::property_map&
iscool::preferences::store::get_properties() const
{
    return _preferences;
}

void iscool::preferences::store::reset( const property_map& values )
{
    _dirty.clear();
    _pending_changes.clear();
    _save_connection.disconnect();
    
    _preferences = values;
}

void iscool::preferences::store::abort_save()
{
    assert( !_pending_changes.empty() );

    detail::copy_new_fields visitor( _dirty );
    _pending_changes.visit( visitor );
    _pending_changes.clear();

    _save_connection.disconnect();
}

void iscool::preferences::store::schedule_save()
{
    if( _save_connection.connected() || _dirty.empty()
        || !_pending_changes.empty() )
        return;

    if ( _flush_delay == std::chrono::milliseconds::zero() )
        _save_connection =
            iscool::schedule::delayed_call( std::bind( &store::save, this ) );
    else
        _save_connection =
            iscool::schedule::delayed_call
            ( std::bind( &store::save, this ), _flush_delay );
}

void iscool::preferences::store::save()
{
    _save_connection.disconnect();
    
    assert( _pending_changes.empty() );
    _pending_changes.swap( _dirty );

    _save_delegate( _pending_changes );
}

iscool::preferences::detail::copy_new_fields::copy_new_fields
( property_map& target )
    : _target( target )
{

}
                    
template< typename T >
void iscool::preferences::detail::copy_new_fields::operator()
( const std::string& key, const T& value )
{
    if ( !_target.has< T >( key ) )
        _target.set( key, value );
}

iscool::preferences::detail::collect_keys::collect_keys
( std::vector< std::string >& keys )
    : _keys( keys )
{
    
}
        
template< typename T >
void
iscool::preferences::detail::collect_keys::operator()( std::string key, T&& )
{
    const auto begin( _keys.begin() );
    const auto end( _keys.end() );

    if ( std::find( begin, end, key ) == end )
        _keys.emplace_back( std::move( key ) );
}
