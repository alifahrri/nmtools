#!/usr/bin/bash

if [[ -z "${LLVM_VERSION}" ]]; then
    LLVM_VERSION="14"
else
    LLVM_VERSION="${LLVM_VERSION}"
    echo "set LLVM_VERSION from env"
fi

if [[ -z "${ACCELERATED_CPU}" ]]; then
    ACCELERATED_CPU="ON"
else
    ACCELERATED_CPU="${ACCELERATED_CPU}"
    echo "set ACCELERATED_CPU from env"
fi

if [[ -z "${OPENCL_BACKEND}" ]]; then
    OPENCL_BACKEND="OFF"
else
    OPENCL_BACKEND="${OPENCL_BACKEND}"
    echo "set OPENCL_BACKEND from env"
fi

if [[ -z "${CUDA_BACKEND}" ]]; then
    CUDA_BACKEND="OFF"
else
    CUDA_BACKEND="${CUDA_BACKEND}"
    echo "set CUDA_BACKEND from env"
fi

if [[ -z "${LEVEL_ZERO_BACKEND}" ]]; then
    LEVEL_ZERO_BACKEND="OFF"
else
    LEVEL_ZERO_BACKEND="${LEVEL_ZERO_BACKEND}"
    echo "set LEVEL_ZERO_BACKEND from env"
fi

if [[ -z "${BUILD_TYPE}" ]]; then
  BUILD_TYPE="Release"
else
  BUILD_TYPE="${BUILD_TYPE}"
  echo "set BUILD_TYPE from env"
fi

echo "using LLVM_VERSION=${LLVM_VERSION}"
echo "using ACCELERATED_CPU=${ACCELERATED_CPU}"
echo "using OPENCL_BACKEND=${OPENCL_BACKEND}"
echo "using CUDA_BACKEND=${CUDA_BACKEND}"
echo "using LEVEL_ZERO_BACKEND=${LEVEL_ZERO_BACKEND}"

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

apt install -y python3-dev libpython3-dev \
    build-essential cmake git pkg-config \
    make ninja-build apt-utils \
    intel-opencl-icd clinfo \
    libboost-context-dev libboost-fiber-dev \
    libomp-dev libomp-${LLVM_VERSION}-dev libgomp1 \
    libclang-${LLVM_VERSION}-dev clang-${LLVM_VERSION} \
    llvm-${LLVM_VERSION} libclang-cpp${LLVM_VERSION}-dev libclang-cpp${LLVM_VERSION} \
    llvm-${LLVM_VERSION}-dev --fix-missing

cd ${DIR}

mkdir -p build

cd build

cmake \
    -DLLVM_DIR=/usr/lib/llvm-${LLVM_VERSION}/cmake \
    -DWITH_ACCELERATED_CPU=${ACCELERATED_CPU} \
    -DWITH_OPENCL_BACKEND=${OPENCL_BACKEND} \
    -DWITH_CUDA_BACKEND=${CUDA_BACKEND} \
    -DWITH_LEVEL_ZERO_BACKEND=${LEVEL_ZERO_BACKEND} \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    ..
make -j2 VERBOSE=1
make install