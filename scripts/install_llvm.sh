#!/bin/bash
set -euo pipefail

if [[ -z "${LLVM_VERSION:-}" ]]; then
  LLVM_VERSION="14"
else
  echo "set LLVM_VERSION from env: ${LLVM_VERSION}"
fi

# Some CI resolvers return IPv6 addresses while IPv6 egress is unavailable.
# Force IPv4 for APT and for wget invocations made by helper scripts.
printf 'Acquire::ForceIPv4 "true";\n' > /etc/apt/apt.conf.d/99force-ipv4

# Update and install prerequisites
apt update && apt install -y lsb-release wget ca-certificates software-properties-common gnupg

WGET_BIN="$(command -v wget)"
WGET_WRAPPER_DIR="$(mktemp -d)"
trap 'rm -rf "${WGET_WRAPPER_DIR}"' EXIT
cat > "${WGET_WRAPPER_DIR}/wget" <<EOF
#!/usr/bin/env bash
exec "${WGET_BIN}" -4 "\$@"
EOF
chmod +x "${WGET_WRAPPER_DIR}/wget"
export PATH="${WGET_WRAPPER_DIR}:${PATH}"

# Clean up any existing LLVM installations and OpenMP conflicts
apt-get purge -y libomp-* llvm-* llvm-*dev || true
apt-get autoremove -y || true
apt-get autoclean -y || true

# Install LLVM
wget --tries=5 --timeout=30 --wait=5 -O llvm.sh https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
./llvm.sh "${LLVM_VERSION}"

apt-get install -y "libomp-${LLVM_VERSION}-dev"

# Set up alternatives (important for selecting the correct LLVM version)
update-alternatives --install /usr/bin/llvm-config llvm-config "/usr/bin/llvm-config-${LLVM_VERSION}" 200

# Verify the installation
which llvm-config
"llvm-config-${LLVM_VERSION}" --version --prefix --bindir --includedir --libdir --cmakedir

# Crucial: Install the development package containing the LLVM CMake package
apt-get install -y "llvm-${LLVM_VERSION}-dev"

# Double-check the CMake package used by SPIRV-LLVM-Translator and AdaptiveCpp.
LLVM_CMAKE_DIR="$(llvm-config-"${LLVM_VERSION}" --cmakedir)"
if [[ ! -f "${LLVM_CMAKE_DIR}/LLVMConfig.cmake" ]]; then
  echo "LLVMConfig.cmake not found in ${LLVM_CMAKE_DIR}" >&2
  exit 1
fi
echo "found LLVM CMake config: ${LLVM_CMAKE_DIR}/LLVMConfig.cmake"

# For CMake projects, set the LLVM_DIR variable
export LLVM_DIR="${LLVM_CMAKE_DIR}"