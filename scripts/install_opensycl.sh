#!/usr/bin/bash

git clone --single-branch -b v0.9.4 https://github.com/OpenSYCL/OpenSYCL

cd OpenSYCL

mkdir -p build

cd build

cmake -DLLVM_DIR=/usr/lib/llvm-14/cmake -DWITH_CUDA_BACKEND=OFF -DWITH_CUDA_NVCXX_ONLY=ON ..
make -j2 VERBOSE=1
make install