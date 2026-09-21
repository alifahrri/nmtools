#!/bin/bash
set -euo pipefail

if [[ -z "${LLVM_VERSION:-}" ]]; then
  LLVM_VERSION="14"
else
  echo "set LLVM_VERSION from env: ${LLVM_VERSION}"
fi

if [[ -z "${LLVM_SPV_VERSION:-}" ]]; then
  LLVM_SPV_VERSION="v14.0.0"
else
  echo "set LLVM_SPV_VERSION from env: ${LLVM_SPV_VERSION}"
fi

echo "using LLVM_VERSION=${LLVM_VERSION}"

echo "using LLVM_SPV_VERSION=${LLVM_SPV_VERSION}"

LLVM_DIR="/usr/lib/llvm-${LLVM_VERSION}/cmake"
if [[ ! -f "${LLVM_DIR}/LLVMConfig.cmake" ]]; then
  echo "LLVMConfig.cmake not found in ${LLVM_DIR}; run scripts/install_llvm.sh first" >&2
  exit 1
fi

DIR=SPIRV-LLVM-Translator
GIT_REPOSITORY=https://github.com/KhronosGroup/SPIRV-LLVM-Translator
if [[ -d "$DIR" ]]; then
    echo "$DIR exists. skipping cloning"
else
    git clone ${GIT_REPOSITORY}
fi
cd SPIRV-LLVM-Translator
git fetch && git checkout ${LLVM_SPV_VERSION}

mkdir -p build
cd build
cmake -DLLVM_DIR="${LLVM_DIR}" ..
make llvm-spirv -j2
make install
cp tools/llvm-spirv/llvm-spirv /usr/local/bin