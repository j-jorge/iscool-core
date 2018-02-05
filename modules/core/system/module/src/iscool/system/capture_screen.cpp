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
#include "iscool/system/capture_screen.h"

#include "iscool/system/detail/capture_screen_delegate.h"
#include "iscool/system/detail/capture_screen_signal_pool.h"

#include "iscool/signals/signal.impl.tpp"

#include <boost/bind.hpp>

#include <cassert>

namespace iscool
{
    namespace system
    {
        namespace detail
        {
            static capture_screen_signal_pool signal_pool( 1 );
        }
    }
}

iscool::signals::connection iscool::system::capture_screen
( const std::string& file_name,
  boost::function< void ( std::string ) > on_done )
{
    assert( !detail::capture_screen_delegate.empty() );

    const auto slot( detail::signal_pool.pick_available_signal() );
    const iscool::signals::connection result( slot.value.connect( on_done ) );
    
    detail::capture_screen_delegate
        ( file_name,
          boost::bind
          ( &detail::capture_screen_signal_pool::process_capture,
            &detail::signal_pool, slot.id, _1 ) );

    assert( result.connected() );
    
    return result;
}
