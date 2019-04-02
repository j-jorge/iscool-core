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
#include "iscool/style/declaration.h"

#include "iscool/style/detail/get_properties_pool.h"
#include "iscool/style/detail/shared_properties.h"

#include "iscool/none.h"
#include "iscool/optional.impl.tpp"

namespace iscool
{
    namespace style
    {
        namespace detail
        {
            static const shared_properties empty_properties;
        }
    }
}

template class iscool::optional< const iscool::style::declaration& >;
template class iscool::optional< iscool::style::declaration >;

void
iscool::style::declaration::set_number( const std::string& key, float value )
{
    ensure_owned_properties();
    _properties->numbers[ key ] = value;
}

iscool::optional< float >
iscool::style::declaration::get_number( const std::string& key ) const
{
    if ( !_properties )
        return iscool::none;

    const auto result( _properties->numbers.find( key ) );

    if ( result == _properties->numbers.end() )
        return iscool::none;

    return result->second;
}

float iscool::style::declaration::get_number
( const std::string& key, float default_value ) const
{
    const iscool::optional< float > result( get_number( key ) );

    if ( !result )
        return default_value;

    return *result;
}

void
iscool::style::declaration::set_boolean( const std::string& key, bool value )
{
    ensure_owned_properties();
    _properties->booleans[ key ] = value;
}

iscool::optional< bool >
iscool::style::declaration::get_boolean( const std::string& key ) const
{
    if ( !_properties )
        return iscool::none;
    
    const auto result( _properties->booleans.find( key ) );

    if ( result == _properties->booleans.end() )
        return iscool::none;

    return result->second;
}

bool iscool::style::declaration::get_boolean
( const std::string& key, bool default_value ) const
{
    const iscool::optional< bool > result( get_boolean( key ) );

    if ( !result )
        return default_value;

    return *result;
}

void iscool::style::declaration::set_string
( const std::string& key, const std::string& value)
{
    ensure_owned_properties();
    _properties->strings[ key ] = value;
}

iscool::optional< std::string >
iscool::style::declaration::get_string( const std::string& key ) const
{
    if ( !_properties )
        return iscool::none;
    
    const auto result( _properties->strings.find( key ) );

    if ( result == _properties->strings.end() )
        return iscool::none;

    return result->second;
}

std::string
iscool::style::declaration::get_string
( const std::string& key, const std::string& default_value ) const
{
    const iscool::optional< std::string > result( get_string( key ) );

    if ( !result )
        return default_value;

    return *result;
}

void iscool::style::declaration::set_declaration
( const std::string& key, const declaration& style )
{
    ensure_owned_properties();
    *_properties->declarations[ key ] = style;
}

iscool::optional< const iscool::style::declaration& >
iscool::style::declaration::get_declaration( const std::string& key ) const
{
    if ( !_properties )
        return iscool::none;
    
    const declaration_map::const_iterator it
        ( _properties->declarations.find( key ) );

    if ( it == _properties->declarations.end() )
        return iscool::none;
    else
        return *it->second;
}

const iscool::style::declaration&
iscool::style::declaration::get_declaration_or_empty
( const std::string& key ) const
{
    const iscool::optional< const declaration& > result
        ( get_declaration( key ) );

    if ( result )
        return *result;
    
    static declaration empty;
    return empty;
}

iscool::style::declaration
iscool::style::declaration::merge( declaration style ) const
{
    if ( !_properties )
        return style;

    if ( !style._properties )
    {
        style._properties = _properties;
        return style;
    }

    style.ensure_owned_properties();

    style._properties->numbers.insert
        ( _properties->numbers.begin(), _properties->numbers.end() );
    style._properties->booleans.insert
        ( _properties->booleans.begin(), _properties->booleans.end() );
    style._properties->strings.insert
        ( _properties->strings.begin(), _properties->strings.end() );

    style._properties->declarations = get_merged_declarations( style );

    return style;
}

bool iscool::style::declaration::is_empty() const
{
    return !_properties;
}

iscool::style::declaration::numbers_range
iscool::style::declaration::get_numbers() const
{
    if ( !_properties )
        return
            numbers_range
            ( detail::empty_properties.values.numbers.begin(),
              detail::empty_properties.values.numbers.end() );
    
    return
        numbers_range
        ( _properties->numbers.begin(), _properties->numbers.end() );
}

iscool::style::declaration::booleans_range
iscool::style::declaration::get_booleans() const
{
    if ( !_properties )
        return
            booleans_range
            ( detail::empty_properties.values.booleans.begin(),
              detail::empty_properties.values.booleans.end() );
    
    return
        booleans_range
        ( _properties->booleans.begin(), _properties->booleans.end() );
}

iscool::style::declaration::strings_range
iscool::style::declaration::get_strings() const
{
    if ( !_properties )
        return
            strings_range
            ( detail::empty_properties.values.strings.begin(),
              detail::empty_properties.values.strings.end() );
    
    return
        strings_range
        ( _properties->strings.begin(), _properties->strings.end() );
}

iscool::style::declaration::declarations_range
iscool::style::declaration::get_declarations() const
{
    if ( !_properties )
        return
            declarations_range
            ( detail::empty_properties.values.declarations.begin(),
              detail::empty_properties.values.declarations.end() );
    
    return
        declarations_range
        ( _properties->declarations.begin(), _properties->declarations.end() );
}

std::uint64_t iscool::style::declaration::get_id() const
{
    if ( !_properties )
        return detail::empty_properties.get_id();
    
    return _properties.get_id();
}

iscool::style::declaration::declaration_map
iscool::style::declaration::get_merged_declarations
( const declaration& style ) const
{
    assert ( style._properties );
    assert ( _properties );
    
    declaration_map result( _properties->declarations );

    for ( const declaration_map::value_type& sub_style
              : style._properties->declarations )
        *result[ sub_style.first ] =
            result[ sub_style.first ]->merge( sub_style.second );

    return result;
}

void iscool::style::declaration::ensure_owned_properties()
{
    if ( !_properties )
    {
        _properties.alloc();
        return;
    }

    if ( _properties.is_unique() )
        return;

    detail::properties_handle new_properties;
    new_properties.alloc();
    *new_properties = *_properties;
    _properties = new_properties;
}
