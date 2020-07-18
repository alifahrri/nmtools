#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
xsimd_url="https://github.com/xtensor-stack/xsimd/archive/7.4.8.tar.gz"
xsimd_file="7.4.8.tar.gz"
xsimd_dir="xsimd-7.4.8"

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -d|--dest)
    DEST="$2"
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

if [ -z "$DEST" -a "$DEST" != " " ]; then
    DEST="/opt"
fi

wget -O $DEST/$xsimd_file $xsimd_url

cd $DEST
tar -zxvf $xsimd_file

cd $xsimd_dir
mkdir -p build && cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local/ .. && make install

cd $CWD