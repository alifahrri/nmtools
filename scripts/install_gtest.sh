#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 
googletest_url="https://github.com/google/googletest/archive/release-1.10.0.tar.gz"
googletest_file="release-1.10.0.tar.gz"
googletest_dir="googletest-release-1.10.0"

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

wget -O $DEST/$googletest_file $googletest_url

cd $DEST
tar -zxvf $googletest_file

cd $googletest_dir && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    make && make install

cd $CWD