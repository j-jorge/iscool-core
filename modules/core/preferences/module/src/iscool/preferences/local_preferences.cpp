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
#include "iscool/preferences/local_preferences.h"

#include "iscool/preferences/log_context.h"

#include "iscool/json/write_to_stream.h"
#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"

#include <fstream>

namespace iscool
{
    namespace preferences
    {
        namespace detail
        {
            class copy_all_fields
            {
            public:
                explicit copy_all_fields( Json::Value& target );

                template< typename T >
                void operator()( const std::string& key, const T& value );

            private:
                Json::Value& _target;
            };
        }
    }
}

void iscool::preferences::local_preferences::flush()
{
    if ( _store.is_dirty() )
        _store.flush();
}
            
int iscool::preferences::local_preferences::get_value
( const std::string& key, int default_value ) const
{
    return _store.get_value( key, default_value );
}

void iscool::preferences::local_preferences::set_value
( const std::string& key, int value )
{
    _store.set_value( key, value );
}
            
bool iscool::preferences::local_preferences::get_value
( const std::string& key, bool default_value ) const
{
    return _store.get_value( key, default_value );
}

void iscool::preferences::local_preferences::set_value
( const std::string& key, bool value )
{
    _store.set_value( key, value );
}
            
std::string iscool::preferences::local_preferences::get_value
( const std::string& key, const std::string& default_value ) const
{
    return _store.get_value( key, default_value );
}

void iscool::preferences::local_preferences::set_value
( const std::string& key, const std::string& value )
{
    _store.set_value( key, value );
}

void iscool::preferences::local_preferences::save( const property_map& dirty )
{
    detail::copy_all_fields visitor( _values );
    dirty.visit( visitor );

    std::ofstream file( _file_path );
    
    if ( iscool::json::write_to_stream( file, _values ) && file )
        _store.confirm_save();
    else
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "Could not save the local preferences" );
        _store.save_error();
    }
}

iscool::preferences::detail::copy_all_fields::copy_all_fields
( Json::Value& target )
    : _target( target )
{

}

template< typename T >
void iscool::preferences::detail::copy_all_fields::operator()
( const std::string& key, const T& value )
{
    _target[ key ] = value;
}

