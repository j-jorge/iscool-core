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
#ifndef ISCOOL_FILES_TEST_FILE_SYSTEM_DELEGATES_MOCKUP_H
#define ISCOOL_FILES_TEST_FILE_SYSTEM_DELEGATES_MOCKUP_H

#include "iscool/files/file_system_delegates.h"

#include <boost/function.hpp>

namespace iscool
{
    namespace files
    {
        class file_system_delegates;
        
        namespace test
        {
            class file_system_delegates_mockup:
                public iscool::files::file_system_delegates
            {
            public:
                file_system_delegates_mockup();
                
                std::unique_ptr< std::istream > read_file
                ( const std::string& path ) const override;
            
                std::string get_writable_path() const override;
                bool file_exists( const std::string& path ) const override;

                std::string get_full_path
                ( const std::string& path ) const override;
                    
            public:
                boost::function
                <
                    std::unique_ptr< std::istream >( const std::string& )
                > read_file_impl;
            
                boost::function< std::string() > get_writable_path_impl;
             
                boost::function< bool( const std::string& ) >
                file_exists_impl;
                    
                boost::function< std::string( const std::string& ) >
                get_full_path_impl;
            };

            const iscool::files::file_system_delegates&
            default_file_system_delegates_mockup();
        }
    }
}

#endif
