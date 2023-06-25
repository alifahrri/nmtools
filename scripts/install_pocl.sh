#!/bin/bash

if [[ -z "${LLVM_VERSION}" ]]; then
  LLVM_VERSION="14"
else
  LLVM_VERSION="${LLVM_VERSION}"
  echo "set LLVM_VERSION from env"
fi

if [[ -z "${POCL_VERSION}" ]]; then
  POCL_VERSION="v3.1"
else
  POCL_VERSION="${POCL_VERSION}"
  echo "set POCL_VERSION from env"
fi

echo "using LLVM_VERSION=${LLVM_VERSION}"

echo "using POCL_VERSION=${POCL_VERSION}"

DIR=pocl
if [[ -d "$DIR" ]]; then
    echo "$DIR exists. skipping cloning"
else
    git clone https://github.com/pocl/pocl.git
fi

apt install -y xxd python3-dev libpython3-dev build-essential ocl-icd-libopencl1 intel-opencl-icd \
    cmake git pkg-config libclang-${LLVM_VERSION}-dev clang \
    llvm-${LLVM_VERSION} make ninja-build ocl-icd-libopencl1 ocl-icd-dev \
    ocl-icd-opencl-dev libhwloc-dev zlib1g zlib1g-dev clinfo dialog apt-utils \
    libxml2-dev libclang-cpp${LLVM_VERSION}-dev libclang-cpp${LLVM_VERSION} \
    llvm-${LLVM_VERSION}-dev --fix-missing

cd ${DIR}
git checkout ${POCL_VERSION}
mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_CUDA=OFF -DSPIRV=ON -DLLVM_SPIRV=/usr/local/bin/llvm-spirv -DCMAKE_INSTALL_PREFIX=/usr .. \
    && make -j2 && make install