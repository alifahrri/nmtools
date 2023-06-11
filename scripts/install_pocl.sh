#!/bin/bash

git clone -b v3.1 --single-branch https://github.com/pocl/pocl.git

export LLVM_VERSION=14
apt install -y xxd python3-dev libpython3-dev build-essential ocl-icd-libopencl1 \
    cmake git pkg-config libclang-${LLVM_VERSION}-dev clang \
    llvm-${LLVM_VERSION} make ninja-build ocl-icd-libopencl1 ocl-icd-dev \
    ocl-icd-opencl-dev libhwloc-dev zlib1g zlib1g-dev clinfo dialog apt-utils \
    libxml2-dev libclang-cpp${LLVM_VERSION}-dev libclang-cpp${LLVM_VERSION} \
    llvm-${LLVM_VERSION}-dev --fix-missing

cd pocl && mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_CUDA=OFF -DSPIRV=ON -DLLVM_SPIRV=/usr/local/bin/llvm-spirv -DCMAKE_INSTALL_PREFIX=/usr .. \
    && make -j2 && make install