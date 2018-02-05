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
#ifndef ISCOOL_MONITORING_DECLARE_PROGRESS_TRACKER_H
#define ISCOOL_MONITORING_DECLARE_PROGRESS_TRACKER_H

#include <boost/function.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>

#include <climits>

#define ic_monitoring_detail_enum_value( r, data, i, seq ) \
    BOOST_PP_COMMA_IF( i ) seq = ( bit_field( 1 ) << i )

#define ic_monitoring_detail_list_enum_values( names ) \
    BOOST_PP_SEQ_FOR_EACH_I( ic_monitoring_detail_enum_value, _, names )

#define ic_monitoring_declare_progress_tracker( type, names )    \
    class type                                                   \
    {                                                            \
    private:                                                     \
        typedef unsigned int bit_field;                          \
                                                                 \
        static_assert                                            \
            ( BOOST_PP_SEQ_SIZE( names ) != 0,                   \
              "progress_tracker " BOOST_PP_STRINGIZE( type )     \
              " needs at least one state." );                    \
                                                                 \
        static_assert                                            \
            ( BOOST_PP_SEQ_SIZE( names )                         \
              < sizeof( bit_field ) * CHAR_BIT,                  \
              "Too many steps in progress_tracker "              \
              BOOST_PP_STRINGIZE( type ) "." );                  \
                                                                 \
    public:                                                      \
        enum class step: bit_field                               \
        {                                                        \
            ic_monitoring_detail_list_enum_values( names )       \
        };                                                       \
                                                                 \
    public:                                                      \
        type();                                                  \
        explicit type                                            \
            ( const boost::function< void() >& on_completed );   \
                                                                 \
        void done( step s );                                     \
                                                                 \
        void reset();                                            \
                                                                 \
        void reset                                               \
            ( const boost::function< void() >& on_completed );   \
                                                                 \
    private:                                                     \
        static constexpr bit_field all_mask =                    \
            ( bit_field( 1 ) << BOOST_PP_SEQ_SIZE( names ) )     \
            - 1;                                                 \
                                                                 \
        boost::function< void() > _notify_completed;             \
        bit_field _done_steps;                                   \
    }



#endif
