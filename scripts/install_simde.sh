#!/bin/bash

if [[ -z "${SIMDE_VERSION}" ]]; then
    SIMDE_VERSION="v0.7.6"
else
    echo "set SIMDE_VERSION from env"
fi

echo "using SIMDE_VERSION=${SIMDE_VERSION}"

DIR=simde
if [[ -d "${DIR}" ]]; then
    echo "${DIR} exists, skip cloning"
else
    git clone --single-branch -b ${SIMDE_VERSION} https://github.com/simd-everywhere/simde.git
fi

# sudo apt-get install -y ninja-build ninja-build python3-pip
# pip3 install meson==0.55.0

cd ${DIR}
mkdir -p build
meson setup build --prefix=/usr/local -Dtests=false
ninja -C build install