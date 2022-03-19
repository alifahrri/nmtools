#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -b|--build-dir)
    BUILD_DIR="$2"
    shift # past argument
    shift # past value
    ;;
    *)    # unknown option
    POSITIONAL+=("$1") # save it in an array for later
    shift # past argument
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

if [ -z "$BUILD_DIR" -a "$BUILD_DIR" != " " ]; then
    BUILD_DIR="$DIR/../build/Release"
fi

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake -DNMTOOLS_BUILD_TESTBENCH=ON \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DNMTOOLS_TEST_ALL=OFF \
    -DNMTOOLS_BUILD_META_TESTS=OFF \
    -DNMTOOLS_BUILD_UTL_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    ${DIR}/..
make -j${nproc} VERBOSE=1