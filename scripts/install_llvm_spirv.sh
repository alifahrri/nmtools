#!/bin/bash

git clone https://github.com/KhronosGroup/SPIRV-LLVM-Translator
cd SPIRV-LLVM-Translator
git checkout v14.0.0

mkdir -p build
cd build
cmake ..
make llvm-spirv -j2
make install
cp tools/llvm-spirv/llvm-spirv /usr/local/bin