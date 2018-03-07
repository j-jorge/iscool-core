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
package iscool.jni;

import iscool.jni.NativeCall;

public final class CallbackHelper {
    private long _callback = 0;

    public void configure( long callback ) {
        assert _callback == 0;
        _callback = callback;
    }

    public void trigger( final Object... args ) {
        if ( _callback == 0 )
            return;

        final long callback = _callback;
        _callback = 0;

        NativeCall.call( callback, args );
    }
}
