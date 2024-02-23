#!/usr/bin/bash

DIR=OpenSYCL
GIT_REPOSITORY=https://github.com/OpenSYCL/OpenSYCL
# VERSION=v0.9.4
# DIR=AdaptiveCpp
# GIT_REPOSITORY=https://github.com/AdaptiveCpp/AdaptiveCpp.git
VERSION=v23.10.0
if [[ -d "$DIR" ]]; then
    echo "$DIR exists. skipping cloning"
else
    git clone --single-branch -b ${VERSION}  ${GIT_REPOSITORY}
fi

cd ${DIR}

mkdir -p build

cd build

cmake \
    -DLLVM_DIR=/usr/lib/llvm-14/cmake \
    -DWITH_ACCELERATED_CPU=ON \
    -DCMAKE_BUILD_TYPE=Release \
    ..
make -j2 VERBOSE=1
make install