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
#ifndef ISCOOL_JNI_HASH_MAP_TPP
#define ISCOOL_JNI_HASH_MAP_TPP

#include "iscool/jni/alloc.h"
#include "iscool/jni/collection.h"
#include "iscool/jni/get_method.h"
#include "iscool/jni/iterator.h"
#include "iscool/jni/method_jobject.h"

template< typename K, typename V >
iscool::jni::hash_map< K, V >::hash_map()
    : _map( alloc( "java/util/HashMap", "()V" ) )
{
    
}
        
template< typename K, typename V >
iscool::jni::hash_map< K, V >::hash_map( const java_ptr< jobject >& impl )
    : _map( impl )
{

}

template< typename K, typename V >
const iscool::jni::java_ptr< jobject >&
iscool::jni::hash_map< K, V >::get_java_object() const
{
    return _map;
}

template< typename K, typename V >
typename iscool::jni::hash_map< K, V >::value_type
iscool::jni::hash_map< K, V >::put
( const key_type& key, const value_type& value ) const
{
    const auto method
        ( get_method< jobject >
          ( "java/util/HashMap", "put",
            "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;" ) );

    jobject result( method( _map, key, value ) );
    return value_type( static_cast< V >( result ) );
}

template< typename K, typename V >
std::vector< iscool::jni::map_entry< K, V > >
iscool::jni::hash_map< K, V >::get_entry_set() const
{
    const auto method
        ( get_method< jobject >
          ( "java/util/HashMap", "entrySet", "()Ljava/util/Set;" ) );

    const collection< jobject > entry_set( method( _map ) );
    iterator< jobject > it( entry_set.get_iterator() );

    std::vector< map_entry< K, V > > result;
    
    while ( it.has_next() )
        result.emplace_back( it.next() );

    return result;
}

template< typename K, typename V >
jobject
iscool::jni::detail::get_method_argument_impl
<
    iscool::jni::hash_map< K, V >
>::get
( const hash_map< K, V >& map )
{
    return map.get_java_object().get();
}

#endif
