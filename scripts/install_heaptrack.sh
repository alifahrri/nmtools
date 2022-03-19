#!/bin/bash

url=https://github.com/KDE/heaptrack/archive/refs/tags/v1.3.0.tar.gz
dir=heaptrack-1.3.0
file=v1.3.0.tar.gz

cd /opt

if [ ! -d ${dir} ]; then
  if [ ! -f ${file} ]; then
    wget ${url}
  fi
  tar -zxvf ${file}
fi

cd ${dir}
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
make install
