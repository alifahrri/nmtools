#!/bin/bash

if [[ -z "${LLVM_SPV_VERSION}" ]]; then
  LLVM_SPV_VERSION="v14.0.0"
else
  LLVM_SPV_VERSION="${LLVM_SPV_VERSION}"
fi

git clone https://github.com/KhronosGroup/SPIRV-LLVM-Translator
cd SPIRV-LLVM-Translator
git checkout ${LLVM_SPV_VERSION}

mkdir -p build
cd build
cmake ..
make llvm-spirv -j2
make install
cp tools/llvm-spirv/llvm-spirv /usr/local/bin