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
#include "iscool/preferences/property_deserializer.h"

#include "iscool/preferences/log_context.h"

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"
#include "iscool/log/nature/info.h"
#include "iscool/preferences/property_map.impl.h"

#include <boost/lexical_cast.hpp>

void iscool::preferences::property_deserializer::add_int64_property
( const std::string& key )
{
    add_key( _int64, key );
}

void iscool::preferences::property_deserializer::add_bool_property
( const std::string& key )
{
    add_key( _bool, key );
}

void iscool::preferences::property_deserializer::add_float_property
( const std::string& key )
{
    add_key( _float, key );
}

void iscool::preferences::property_deserializer::add_string_property
( const std::string& key )
{
    add_key( _string, key );
}

void iscool::preferences::property_deserializer::remove_int64_property
( const std::string& key )
{
    _int64.erase( key );
}

void iscool::preferences::property_deserializer::remove_bool_property
( const std::string& key )
{
    _bool.erase( key );
}

void iscool::preferences::property_deserializer::remove_float_property
( const std::string& key )
{
    _float.erase( key );
}

void iscool::preferences::property_deserializer::remove_string_property
( const std::string& key )
{
    _string.erase( key );
}

std::vector< std::string >
iscool::preferences::property_deserializer::get_all_keys() const
{
    std::vector< std::string > result;
    result.reserve
        ( _int64.size() +  _bool.size() + _float.size() + _string.size() );

    result.insert( result.end(), _int64.begin(), _int64.end() );
    result.insert( result.end(), _bool.begin(), _bool.end() );
    result.insert( result.end(), _float.begin(), _float.end() );
    result.insert( result.end(), _string.begin(), _string.end() );

    return result;
}

void iscool::preferences::property_deserializer::merge
( const property_deserializer& that )
{
    for ( const std::string& k : that._int64 )
        add_key( _int64, k );

    for ( const std::string& k : that._bool )
        add_key( _bool, k );

    for ( const std::string& k : that._float )
        add_key( _float, k );

    for ( const std::string& k : that._string )
        add_key( _string, k );
}

void iscool::preferences::property_deserializer::operator()
( property_map& result,
  const std::unordered_map< std::string, std::string >& properties ) const
{
    for( const auto& entry : properties )
        if ( _int64.find( entry.first ) != _int64.end() )
            set_int64_value( entry.first, entry.second, result );
        else if ( _bool.find( entry.first ) != _bool.end() )
            set_bool_value( entry.first, entry.second, result );
        else if ( _float.find( entry.first ) != _float.end() )
            set_float_value( entry.first, entry.second, result );
        else if ( _string.find( entry.first ) != _string.end() )
            set_string_value( entry.first, entry.second, result );
        else
            ic_causeless_log
                ( iscool::log::nature::info(), log_context(),
                  "Skipping unexpected property '%s=%s'", entry.first,
                  entry.second );
}

void iscool::preferences::property_deserializer::add_key
( std::unordered_set< std::string >& domain, const std::string& key )
{
    assert( _int64.find( key ) == _int64.end() );
    assert( _string.find( key ) == _string.end() );
    assert( _bool.find( key ) == _bool.end() );
    assert( _float.find( key ) == _float.end() );

    domain.insert( domain.end(), key );
}

void iscool::preferences::property_deserializer::set_int64_value
( const std::string& key, const std::string& value, property_map& result ) const
{
    try
    {
        result.set( key, boost::lexical_cast< std::int64_t >( value ) );
    }
    catch( const boost::bad_lexical_cast& e )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "Failed to convert value to int64 '%s=%s': %s", key, value,
              e.what() );
    }
}

void iscool::preferences::property_deserializer::set_bool_value
( const std::string& key, const std::string& value, property_map& result ) const
{
    try
    {
        result.set( key, boost::lexical_cast< bool >( value ) );
    }
    catch( const boost::bad_lexical_cast& e )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "Failed to convert value to bool '%s=%s': %s", key, value,
              e.what() );
    }
}

void iscool::preferences::property_deserializer::set_float_value
( const std::string& key, const std::string& value, property_map& result ) const
{
    try
    {
        result.set( key, boost::lexical_cast< float >( value ) );
    }
    catch( const boost::bad_lexical_cast& e )
    {
        ic_causeless_log
            ( iscool::log::nature::error(), log_context(),
              "Failed to convert value to float '%s=%s': %s", key, value,
              e.what() );
    }
}

void iscool::preferences::property_deserializer::set_string_value
( const std::string& key, const std::string& value, property_map& result ) const
{
    result.set( key, value );
}
