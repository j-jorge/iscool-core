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
#ifndef ISCOOL_JNI_ITERATOR_H
#define ISCOOL_JNI_ITERATOR_H

#include "iscool/jni/java_ptr.h"

namespace iscool
{
    namespace jni
    {
        template< typename T >
        class iterator
        {
        public:
            typedef java_ptr< T > value_type;
        
        public:
            explicit iterator( jobject impl );
        
            java_ptr< jobject > get_java_object() const;

            bool has_next() const;
            value_type next() const;
        
        private:
            java_ptr< jobject > _impl;
        };

        namespace detail
        {
            template< typename T >
            struct get_method_argument_impl< iterator< T > >
            {
                static jobject get( const iterator< T >& i );
            };
        }
    }
}

#include "iscool/jni/detail/iterator.tpp"

#endif
