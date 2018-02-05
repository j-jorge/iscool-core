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
#include "iscool/factory/dynamic_factory.h"
#include "iscool/factory/dynamic_factory_registrar.h"
#include "iscool/factory/dynamic_factory.impl.tpp"

#include "iscool/test/debug_crash.h"

#include <gtest/gtest.h>

TEST( iscool_factory_dynamic_factory_registrar, constructor )
{
    const auto factory_function
        ( []() -> int
          {
              return 10;
          } );

    iscool::factory::dynamic_factory< int > factory;
    iscool::factory::dynamic_factory_registrar< int > registrar
        ( factory, "10", factory_function );
    
    EXPECT_EQ( 10, factory.create_by_typename( "10" ) );
    EXPECT_DEBUG_CRASH( factory.create_by_typename( "b" ) );
}
