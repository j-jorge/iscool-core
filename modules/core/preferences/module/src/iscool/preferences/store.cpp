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

#include "iscool/schedule/delayed_call.h"

#include <boost/bind.hpp>

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
        }
    }
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

void iscool::preferences::store::abort_save()
{
    assert( !_pending_changes.empty() );

    detail::copy_new_fields visitor( _dirty );
    _pending_changes.visit( visitor );
    _pending_changes.clear();
}

void iscool::preferences::store::schedule_save()
{
    if( _save_connection.connected() || _dirty.empty()
        || !_pending_changes.empty() )
        return;

    if ( _flush_delay == std::chrono::milliseconds::zero() )
        _save_connection =
            iscool::schedule::delayed_call( boost::bind( &store::save, this ) );
    else
        _save_connection =
            iscool::schedule::delayed_call
            ( boost::bind( &store::save, this ), _flush_delay );
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
