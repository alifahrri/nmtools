#!/bin/bash

if [[ -z "${LLVM_VERSION}" ]]; then
  LLVM_VERSION="15"
else
  LLVM_VERSION="${LLVM_VERSION}"
  echo "set LLVM_VERSION from env: ${LLVM_VERSION}"
fi

apt update && apt install -y lsb-release wget software-properties-common gnupg
if [[ -f "llvm.sh" ]]; then
  rm llvm.sh
fi
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh ${LLVM_VERSION}