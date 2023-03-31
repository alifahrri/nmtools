#!/bin/bash

git clone -b v3.0 --single-branch https://github.com/pocl/pocl.git

cd pocl && mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_CUDA=OFF -DSPIRV=ON -DLLVM_SPIRV=/usr/local/bin/llvm-spirv -DCMAKE_INSTALL_PREFIX=/usr .. \
    && make -j2 && make install