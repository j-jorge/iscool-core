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
#ifndef ISCOOL_SCHEDULE_ASYNC_FUNCTION_H
#define ISCOOL_SCHEDULE_ASYNC_FUNCTION_H

#include "iscool/signals/connection.h"

#include <boost/function.hpp>

#include <deque>

namespace iscool
{
    namespace schedule
    {
        template< typename Signature >
        class async_function
        {
        public:
            async_function();
            
            template< typename F >
            async_function( const F& f );
            async_function( const async_function< Signature >& that );
            ~async_function();
            
            async_function< Signature >&
            operator=( const async_function< Signature >& that );
    
            template< typename... Args >
            void operator()( Args... args );

            bool empty() const;
            
        private:
            template< typename... Args >
            void trigger( Args... args );

        private:
            std::deque< iscool::signals::connection > _connections;
            boost::function< Signature > _function;
        };
    }
}

#include "iscool/schedule/detail/async_function.tpp"

#endif
