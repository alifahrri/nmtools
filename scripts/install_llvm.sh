#!/bin/bash

if [[ -z "${LLVM_VERSION}" ]]; then
  LLVM_VERSION="14"
else
  LLVM_VERSION="${LLVM_VERSION}"
  echo "set LLVM_VERSION from env: ${LLVM_VERSION}"
fi

# Update and install prerequisites
apt update && apt install -y lsb-release wget software-properties-common gnupg

# Clean up any existing LLVM installations and OpenMP conflicts
apt-get purge -y libomp-* llvm-* llvm-*dev  # Remove any potentially conflicting packages
apt-get autoremove -y  # Clean up orphaned packages
apt-get autoclean -y   # Clean up downloaded archives

# Install LLVM
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
./llvm.sh ${LLVM_VERSION}

apt-get install -y libomp-${LLVM_VERSION}-dev

# Set up alternatives (important for selecting the correct LLVM version)
update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-${LLVM_VERSION} 200

# Verify the installation
which llvm-config
llvm-config-${LLVM_VERSION} --version --prefix --bindir --includedir --libdir --cmakedir

# Crucial: Install the development package containing libLLVM.so
apt-get install -y llvm-${LLVM_VERSION}-dev

# Double-check for libLLVM.so.  The path might vary slightly.
ls /usr/lib/llvm-${LLVM_VERSION}/lib/libLLVM.so*  # Check if the file exists

# For CMake projects, set the LLVM_DIR variable
export LLVM_DIR="/usr/lib/llvm-${LLVM_VERSION}/cmake"