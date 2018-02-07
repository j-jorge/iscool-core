#!/bin/sh

set -e

cd $(dirname $0)
SOURCE_ROOT="$PWD/.."

mkdir -p "${SOURCE_ROOT}/build/ios"
cd "${SOURCE_ROOT}/build/ios"

: ${IOS_PLATFORM:=OS}
: ${IOS_ARCH:=armv7}
: ${IOS_INSTALL_PREFIX:="${SOURCE_ROOT}/install/ios"}
: ${IOS_BUILD_TYPE:=release}
: ${IOS_DEPLOYMENT_TARGET=7.0}

: ${GIT:=$(which git)}
: ${PYTHON=$(which python)}

cmake "${SOURCE_ROOT}/build-scripts/cmake/" \
      -DCMAKE_TOOLCHAIN_FILE="${SOURCE_ROOT}/build-scripts/cmake/toolchain/ios.toolchain.cmake" \
      -DGIT_EXECUTABLE=${GIT} \
      -DPYTHON_EXECUTABLE=${PYTHON} \
      -DIOS_PLATFORM=${IOS_PLATFORM} \
      -DIOS_ARCH=${IOS_ARCH} \
      -DIOS_DEPLOYMENT_TARGET=${IOS_DEPLOYMENT_TARGET} \
      -DCMAKE_INSTALL_PREFIX="${IOS_INSTALL_PREFIX}" \
      -DCMAKE_BUILD_TYPE=${IOS_BUILD_TYPE}
