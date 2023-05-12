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
#ifndef ISCOOL_NET_MESSAGE_DESERIALIZER_H
#define ISCOOL_NET_MESSAGE_DESERIALIZER_H

#include "iscool/net/endpoint.h"
#include "iscool/net/message/message_type.h"
#include "iscool/signals/connection.h"

#include <functional>
#include <unordered_map>

namespace iscool
{
    namespace net
    {
        class message;

        class message_deserializer
        {
        public:
            message_deserializer();
            ~message_deserializer();

            void interpret_received_message
            ( const endpoint& endpoint, const message& message ) const;

            template< typename M >
            iscool::signals::connection connect_signal
            ( const std::function< void ( const endpoint&, M ) >& f );

        private:
            class deserializer_base;

            template< typename M >
            class typed_deserializer;

            class deserializer_collection
            {
            private:
                typedef
                std::unordered_map< message_type, deserializer_base* >
                deserializer_map;

            public:
                deserializer_collection() = default;
                ~deserializer_collection();

                deserializer_collection
                ( const deserializer_collection& ) = delete;
                deserializer_collection& operator=
                ( deserializer_collection ) = delete;

                template< typename M >
                iscool::signals::connection
                connect
                ( const std::function
                  <
                      void ( const endpoint&, const M& )
                  >& f );

                void dispatch
                ( const endpoint& endpoint, const message& message ) const;

            private:
                deserializer_map _deserializers;
            };

        private:
            deserializer_collection _deserializers;
        };
    }
}

#endif
