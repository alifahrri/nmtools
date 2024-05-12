#!/bin/bash

if [[ -z "${SIMDE_VERSION}" ]]; then
    SIMDE_VERSION="v0.7.6"
else
    echo "set SIMDE_VERSION from env"
fi

if [[ -z "${SIMDE_INSTALL_PREFIX}" ]]; then
    SIMDE_INSTALL_PREFIX="/usr/local/"
else
    echo "set SIMDE_INSTALL_PREFIX from env"
fi

echo "using SIMDE_VERSION=${SIMDE_VERSION}"
echo "using SIMDE_INSTALL_PREFIX=${SIMDE_INSTALL_PREFIX}"

DIR=simde
if [[ -d "${DIR}" ]]; then
    echo "${DIR} exists, skip cloning"
else
    git clone --single-branch -b ${SIMDE_VERSION} https://github.com/simd-everywhere/simde.git
fi

apt-get install -y ninja-build ninja-build python3-pip pkg-config
pip3 install meson==0.55.0

cd ${DIR}
mkdir -p build
meson setup build --prefix=${SIMDE_INSTALL_PREFIX} -Dtests=false
ninja -C build install