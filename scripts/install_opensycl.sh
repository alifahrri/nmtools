#!/usr/bin/bash

LLVM_VERSION=14
ACCELERATED_CPU=ON
OPENCL_BACKEND=ON
CUDA_BACKEND=ON
BUILD_TYPE=Release

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
    -DLLVM_DIR=/usr/lib/llvm-${LLVM_VERSION}/cmake \
    -DWITH_ACCELERATED_CPU=${ACCELERATED_CPU} \
    -DWITH_OPENCL_BACKEND=${OPENCL_BACKEND} \
    -DWITH_CUDA_BACKEND=${CUDA_BACKEND} \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    ..
make -j2 VERBOSE=1
make install