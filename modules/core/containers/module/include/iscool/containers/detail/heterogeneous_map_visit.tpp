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
#ifndef ISCOOL_CONTAINERS_DETAIL_HETEROGENEOUS_MAP_VISIT_TPP
#define ISCOOL_CONTAINERS_DETAIL_HETEROGENEOUS_MAP_VISIT_TPP

template< typename T, typename U >
void iscool::containers::detail::heterogeneous_map_visit< 0 >::run( T, U )
{
    
}

template< std::size_t N >
template< typename Key, typename Visitor, typename... T >
void iscool::containers::detail::heterogeneous_map_visit< N >::run
( const std::tuple< std::unordered_map< Key, T >... >& maps, Visitor&& visitor )
{
    for ( const auto& entry : std::get< N - 1 >( maps ) )
        visitor( entry.first, entry.second );

    heterogeneous_map_visit< N - 1 >::run( maps, visitor );
}

#endif
