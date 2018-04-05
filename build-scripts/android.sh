#!/bin/sh

set -e

cd $(dirname $0)
SOURCE_ROOT="$PWD/.."

mkdir -p "${SOURCE_ROOT}/build/android"
cd "${SOURCE_ROOT}/build/android"

: ${ANDROID_VERSION:=26}
: ${ANDROID_BUILD_TOOLS_VERSION:=26.0.2}
: ${ANDROID_ABI:=armeabi-v7a}
: ${ANDROID_STL:=gnustl_static}
: ${ANDROID_INSTALL_PREFIX:="${SOURCE_ROOT}/install/android"}
: ${ANDROID_BUILD_TYPE:=release}

cmake "${SOURCE_ROOT}/build-scripts/cmake/" \
      -DCMAKE_SYSTEM_NAME=Android \
      -DCMAKE_SYSTEM_VERSION=${ANDROID_VERSION} \
      -DCMAKE_ANDROID_ARCH_ABI=${ANDROID_ABI} \
      -DCMAKE_ANDROID_NDK="${NDK_ROOT}" \
      -DCMAKE_ANDROID_STL_TYPE=${ANDROID_STL} \
      -DCMAKE_INSTALL_PREFIX="${ANDROID_INSTALL_PREFIX}" \
      -DCMAKE_BUILD_TYPE=${ANDROID_BUILD_TYPE}
