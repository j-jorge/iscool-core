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
#ifndef ISCOOL_JNI_COLLECTION_TPP
#define ISCOOL_JNI_COLLECTION_TPP

#include "iscool/jni/get_method.h"
#include "iscool/jni/method_jint.h"

template< typename T >
iscool::jni::collection< T >::collection( jobject impl )
    : _impl( impl )
{
    
}
        
template< typename T >
iscool::jni::java_ptr< jobject >
iscool::jni::collection< T >::get_java_object() const
{
    return _impl;
}

template< typename T >
std::size_t iscool::jni::collection< T >::size() const
{
    const auto method
        ( get_method< jint >
          ( "java/util/Collection", "size", "()I" ) );

    return method( _impl );
}

template< typename T >
iscool::jni::iterator< T > iscool::jni::collection< T >::get_iterator() const
{
    const auto method
        ( get_method< java_ptr< jobject > >
          ( "java/util/Collection", "iterator", "()Ljava/lang/Object;" ) );

    return iterator< T >( method( _impl ).release() );
}

template< typename T >
jobject
iscool::jni::detail::get_method_argument_impl
<
    iscool::jni::collection< T >
>::get
( const collection< T >& c )
{
    return c.get_java_object().get();
}

#endif
