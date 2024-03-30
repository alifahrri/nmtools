#!/bin/bash

if [[ -z "${LLVM_VERSION}" ]]; then
    LLVM_VERSION="14"
else
    LLVM_VERSION="${LLVM_VERSION}"
    echo "set LLVM_VERSION from env"
fi

if [[ -z "${POCL_VERSION}" ]]; then
    POCL_VERSION="v5.0"
else
    POCL_VERSION="${POCL_VERSION}"
    echo "set POCL_VERSION from env"
fi

if [[ -z "${POCL_BUILD_TYPE}" ]]; then
    POCL_BUILD_TYPE=Release
else
    echo "set POCL_BUILD_TYPE from env"
fi

if [[ -z "${POCL_CUDA}" ]]; then
    POCL_CUDA=OFF
else
    POCL_CUDA="${POCL_CUDA}"
    echo "set POCL_CUDA from env"
fi

LLVM_SPV_PATH=/usr/local/bin/llvm-spirv

echo "using LLVM_VERSION=${LLVM_VERSION}"
echo "using POCL_VERSION=${POCL_VERSION}"
echo "using POCL_BUILD_TYPE=${POCL_BUILD_TYPE}"
echo "using LLVM_SPV_PATH=${LLVM_SPV_PATH}"
echo "POCL_CUDA=${POCL_CUDA}"

apt update && \
apt install -y python3-dev libpython3-dev build-essential ocl-icd-libopencl1 \
    cmake git pkg-config libclang-${LLVM_VERSION}-dev clang-${LLVM_VERSION} \
    llvm-${LLVM_VERSION} make ninja-build ocl-icd-libopencl1 ocl-icd-dev \
    ocl-icd-opencl-dev libhwloc-dev zlib1g zlib1g-dev clinfo dialog apt-utils \
    libxml2-dev libclang-${LLVM_VERSION}-dev libclang-cpp${LLVM_VERSION}-dev libclang-cpp${LLVM_VERSION} \
    llvm-${LLVM_VERSION}-dev --fix-missing

DIR=pocl
GIT_REPOSITORY=https://github.com/pocl/pocl.git
if [[ -d "$DIR" ]]; then
    echo "$DIR exists. skipping cloning"
else
    git clone ${GIT_REPOSITORY}
fi

cd ${DIR}
git fetch && git checkout ${POCL_VERSION}
mkdir -p build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=${POCL_BUILD_TYPE} \
    -DENABLE_TESTS=OFF \
    -DENABLE_CUDA=${POCL_CUDA} \
    -DSPIRV=ON -DLLVM_SPIRV=${LLVM_SPV_PATH} \
    -DCMAKE_INSTALL_PREFIX=/usr .. \
    && make -j2 && make install