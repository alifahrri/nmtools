#!/bin/bash

FILE=amdgpu-install_6.1.60101-1_all.deb
URL=https://repo.radeon.com/amdgpu-install/6.1.1/ubuntu/jammy/amdgpu-install_6.1.60101-1_all.deb

apt update
if [[ -f "$FILE" ]]; then
    echo "$FILE exists skipping downloads"
else
    wget ${URL}
fi
apt install -y ./${FILE}
apt update
apt install -y hipcc
hipcc --version
which hipcc
# amdgpu-install --usecase=lrt --no-dkms