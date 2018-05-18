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
#ifndef ISCOOL_PREFERENCES_LOCAL_PREFERENCES_H
#define ISCOOL_PREFERENCES_LOCAL_PREFERENCES_H

#include "iscool/preferences/store.h"

#include <json/value.h>

#include <condition_variable>
#include <mutex>
#include <thread>

namespace iscool
{
    namespace preferences
    {
        namespace detail
        {
            struct backup_state
            {
                std::condition_variable ready_condition;
                std::mutex mutex;
                bool quit;
                bool available;
            };
        }
        
        class local_preferences
        {
        public:
            local_preferences
            ( const std::chrono::milliseconds& flush_delay,
              const std::string& file_path );
            local_preferences
            ( const std::chrono::milliseconds& flush_delay,
              const std::string& file_path,
              const std::string& backup_extension_format,
              std::size_t backup_count );
            ~local_preferences();
            
            void flush();
            
            int get_value( const std::string& key, int default_value ) const;
            void set_value( const std::string& key, int value );

            bool get_value( const std::string& key, bool default_value ) const;
            void set_value( const std::string& key, bool value );

            std::string get_value
            ( const std::string& key, const std::string& default_value ) const;
            void set_value( const std::string& key, const std::string& value );
            
        private:
            void save( const property_map& dirty );

        private:
            const std::string _file_path;
            const std::string _backup_extension_format;
            
            Json::Value _values;
            store _store;

            detail::backup_state _backup_thread_state;
            std::thread _backup_thread;
        };
    }
}

#endif
