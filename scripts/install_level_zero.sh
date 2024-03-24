#!/usr/bin/bash

DIR=level-zero
GIT_REPOSITORY=https://github.com/oneapi-src/level-zero.git
VERSION=v1.16.9

if [[ -d "$DIR" ]]; then
    echo "${DIR} exists. skipping cloning"
else
    git clone --single-branch -b ${VERSION} ${GIT_REPOSITORY}
fi

cd ${DIR}

mkdir -p build

cd build

cmake ..
cmake --build . --config Release
cmake --build . --config Release --target package
cmake --build . --config Release --target install