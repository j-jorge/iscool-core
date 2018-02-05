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
#ifndef ISCOOL_MONITORING_IMPLEMENT_STATE_MONITOR_H
#define ISCOOL_MONITORING_IMPLEMENT_STATE_MONITOR_H

/*

Example :

ic_implement_state_monitor( test, _test, begin,
                            ( ( begin ) ( ( state1 ) ) )
                            ( ( state1 ) ( ( state2 ) ( end ) ) )
                            ( ( state2 ) ( ( state1 ) ( end ) ) )
                            ( ( end ) ( ) ) ) 

change state with setters :
_test.set_end_state();
_test.set_state1_state();

Check state with testers :
assert( _test.is_begin_state() );
assert( _test.is_end_state() );

*/

#include "iscool/log/causeless_log.h"
#include "iscool/log/nature/error.h"
#include "iscool/memory/pimpl.impl.tpp"
#include "iscool/monitoring/declare_state_monitor.h"

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#include <cassert>

#define ic_detail_state_monitor_state_name( seq )       \
    BOOST_PP_SEQ_ELEM( 0, seq )

#define ic_detail_state_monitor_successor_list( seq )   \
    BOOST_PP_SEQ_ELEM( 1, seq )

#define ic_detail_state_monitor_state_enum_value( seq ) \
    state::ic_detail_state_monitor_state_name( seq )

#define ic_detail_state_monitor_state_value( r, data, i, seq )          \
    BOOST_PP_COMMA_IF( i ) ic_detail_state_monitor_state_name( seq ) 

#define ic_detail_state_monitor_states_enumeration( states )            \
    enum class state : char                                             \
    {                                                                   \
        BOOST_PP_SEQ_FOR_EACH_I( ic_detail_state_monitor_state_value,   \
                                 _, states )                            \
    };


#define ic_detail_state_monitor_is_method_name( name )  \
    BOOST_PP_CAT                                        \
    ( BOOST_PP_CAT( is_, name ), _state() ) 

#define ic_detail_state_monitor_is_method_name_seq( seq ) \
    ic_detail_state_monitor_is_method_name                \
    ( ic_detail_state_monitor_state_name( seq ) )
     
#define ic_detail_state_monitor_is_method( r, data, seq )               \
    bool ic_detail_state_monitor_is_method_name_seq( seq ) const        \
    {                                                                   \
        return _state ==                                                \
            ic_detail_state_monitor_state_enum_value( seq );            \
    } 

#define ic_detail_state_monitor_set_method_name( seq )                  \
    BOOST_PP_CAT                                                        \
    ( BOOST_PP_CAT                                                      \
      ( set_, ic_detail_state_monitor_state_name( seq ) ), _state() )


#define ic_detail_state_monitor_set_method( r, data, seq )              \
    void ic_detail_state_monitor_set_method_name( seq )                 \
    {                                                                   \
        set_state( ic_detail_state_monitor_state_enum_value( seq ) );   \
    }

#define ic_detail_state_monitor_successor_test( r, data, i, seq )  \
    BOOST_PP_IF( i, ||, BOOST_PP_EMPTY() )                         \
    ( data == state::seq )

#define ic_detail_state_monitor_is_successor_case_return( data, successors ) \
    BOOST_PP_IF                                                              \
    ( BOOST_PP_SEQ_SIZE( successors ),                                       \
      BOOST_PP_SEQ_FOR_EACH_I                                                \
      ( ic_detail_state_monitor_successor_test, data, successors ), false )

#define ic_detail_state_monitor_is_successor_case( r, data, seq )       \
    case ic_detail_state_monitor_state_enum_value( seq ):               \
        return ic_detail_state_monitor_is_successor_case_return         \
            ( data, ic_detail_state_monitor_successor_list( seq ) );

#define ic_detail_state_monitor_is_current_state_successor( states )     \
    bool is_current_state_successor( state s ) const                     \
    {                                                                    \
        switch( _state )                                                 \
        {                                                                \
            BOOST_PP_SEQ_FOR_EACH                                        \
                ( ic_detail_state_monitor_is_successor_case, s, states ) \
        default:                                                         \
            assert( false );                                             \
        };                                                               \
        return false;                                                    \
    }

#define ic_detail_state_monitor_to_string_case( r, data, seq )          \
    case ic_detail_state_monitor_state_enum_value( seq ):               \
    return BOOST_PP_STRINGIZE                                           \
        ( ic_detail_state_monitor_state_name( seq ) );

#define ic_detail_state_monitor_state_to_string( states )               \
    static const char* state_to_string( state s )                       \
    {                                                                   \
        switch( s )                                                     \
        {                                                               \
            BOOST_PP_SEQ_FOR_EACH                                       \
                ( ic_detail_state_monitor_to_string_case, _, states )   \
        default:                                                        \
            return nullptr;                                             \
        };                                                              \
    }

#define ic_detail_state_monitor_successor_failed( name, new_state )     \
    ic_causeless_log                                                    \
    ( iscool::log::nature::error(), #name,                              \
      "%s -> %s is not a valid transition.",                            \
      state_to_string( _state ),                                        \
      state_to_string( new_state ) );                                   \
    assert( is_current_state_successor( new_state ) )

#define ic_detail_implement_state_monitor( scope, field_name, initial_state,   \
                                           states )                            \
    class scope state_monitor_ ## field_name                                   \
    {                                                                          \
    public:                                                                    \
        BOOST_PP_SEQ_FOR_EACH( ic_detail_state_monitor_is_method, _, states )  \
        BOOST_PP_SEQ_FOR_EACH( ic_detail_state_monitor_set_method, _, states ) \
    private:                                                                   \
        ic_detail_state_monitor_states_enumeration( states )                   \
        ic_detail_state_monitor_is_current_state_successor( states )           \
        ic_detail_state_monitor_state_to_string( states )                      \
        void set_state( state new_state )                                      \
        {                                                                      \
            if( !is_current_state_successor( new_state ) )                     \
            {                                                                  \
                ic_detail_state_monitor_successor_failed                       \
                    ( scope state_monitor_ ## field_name, new_state );         \
            }                                                                  \
            _state = new_state;                                                \
        }                                                                      \
    private:                                                                   \
        state _state = state::initial_state;                                   \
    };

#define ic_implement_state_monitor( scope, field_name, initial_state, states ) \
    ic_detail_implement_state_monitor                                          \
    ( scope::, field_name, initial_state, states )

#define ic_inline_state_monitor( field_name, initial_state, states )          \
    ic_detail_implement_state_monitor( , field_name, initial_state, states ); \
    iscool::memory::pimpl                                                     \
    <                                                                         \
        state_monitor_ ## field_name,                                         \
        sizeof( state_monitor_ ## field_name )                                \
    > field_name

#endif

