# IsCool Entertainment's General Purpose C++ Library

IsCool Core is a collection of general purpose C++ libraries developed at IsCool Entertainment. This code is used intensively in [Bazoo](http://bazoo-game.com/), Garden of words ([iOS](https://itunes.apple.com/us/app/apple-store/id1291854522?mt=8), [Android](https://play.google.com/store/apps/details?id=com.iscoolentertainment.snc)) and Bouquet of Words ([iOS](https://itunes.apple.com/us/app/apple-store/id1345316417?mt=8), [Android](https://play.google.com/store/apps/details?id=com.iscoolentertainment.wl)).

## What's in it?

The field of application of these libraries varies greatly. You will find some tools to report and handle errors, to create factories, an iterator that can loop over a sequence, yet another logging framework, various memory facilities, an helper to enforce the pimpl usage and a lot more.

Some modules work as an interface to a subsystem that must be plugged in before use. For example, `iscool::audio` contains some functions allowing to play musics and sound effects by relaying the calls to a framework to be defined. The same goes for `iscool::http` which handles the requests but leaves the actual connection to a third party. This design allows us to keep a single unique and consistent interface without coupling our applications with a specific library.

Our games being targeted to mobile devices, there are a few modules specific to these platforms. These modules allow to schedule notifications, to share messages and files through the platform's interface and to call Java functions from C++ and vice versa. These libraries provide a mock up implementation available on desktop systems too.

You will certainly be surprised to see that some libraries implement features already available in other popular libraries (Boost) or even in the standard C++ library. Especially `iscool::any`, `iscool::optional` and `iscool::signals` which behave like Boost.Any, Boost.Optional / `std::optional` and Boost.Signals respectively. Since our code base is C++ 11 only, there are some features from the standard library that we cannot use. For these features we usually fall back to Boost to provide an implementation. In exceptional cases we faced some issues with these implementation in the form of increased compilation time. In this case we implemented our version of the library to keep it minimal and reduce the compilation time.

## Module Directory Structure

The code is located in the `modules` directory, with the libraries in `modules/core` and some test helpers in `modules/testing`.

A library `modules/core/<library>/` has up to five sub directories:
* `module/include` contains the headers,
* `module/src` contains the implementation,
* `tests/` (very rare) contains headers for reusable test classes,
* `tests/src` contains the unit tests,
* `android/java` contains the Java code for the Android part of the module.

## How to build

The build scripts are written in CMake and are available in the `build-scripts/cmake` directory. Shell scripts that launch CMake with the correct arguments for iOS and Android are also available in `build-scripts`.

The libraries depends upon Boost, JsonCpp, and moFileReader. Each of which will be downloaded and compiled during the build unless the variables `USE_DEFAULT_BOOST`, `USE_DEFAULT_JSONCPP` or `USE_DEFAULT_MO_FILE_READER` are respectively defined when executing CMake, in which case the library will be searched using CMake's `find_library()`.

The unit tests require gettext to be installed (especially `msgfmt`) on the host. These tests are written using the Google Test framework which is downloaded and compiled during the build unless `USE_DEFAULT_GOOGLE_TEST` is defined when executing CMake. The unit tests can be skipped by defining `ISCOOL_TEST_ENABLED=0` when executing CMake.

## License

The code is available under the terms of the Apache 2.0 license. See the `LICENSE` file for details.
