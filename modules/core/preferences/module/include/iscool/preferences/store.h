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
#ifndef ISCOOL_PREFERENCES_STORE_H
#define ISCOOL_PREFERENCES_STORE_H

#include "iscool/preferences/property_map.h"
#include "iscool/signals/scoped_connection.h"

#include <boost/function.hpp>

#include <chrono>
#include <vector>

namespace iscool
{
    namespace preferences
    {
        class store
        {
        private:
            typedef
            boost::function< void( const property_map& ) > save_function;
            
        public:
            store
            ( const std::chrono::milliseconds& flush_delay,
              const property_map& initial_values,
              const save_function& save_delegate );

            store( const store& ) = delete;
            store& operator=( const store& ) = delete;
            
            template< typename T >
            void set_value( const std::string& key, const T& value );

            template< typename T >
            T get_value( const std::string& key, const T& default_value ) const;

            bool is_dirty() const;
            void flush();
            void confirm_save();
            void save_error();

            std::vector< std::string > get_keys() const;

        private:
            void abort_save();
            void schedule_save();
            void save();

        private:
            std::chrono::milliseconds _flush_delay;
            property_map _preferences;
            property_map _dirty;
            property_map _pending_changes;
            iscool::signals::scoped_connection _save_connection;
            save_function _save_delegate;
        };
    }
}

#endif
