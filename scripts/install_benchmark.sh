#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 
benchmark_url="https://github.com/google/benchmark/archive/v1.5.1.tar.gz"
benchmark_file="v1.5.1.tar.gz"
benchmark_dir="benchmark-1.5.1"

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

wget -O $DEST/$benchmark_file $benchmark_url

cd $DEST
tar -zxvf $benchmark_file

cd $benchmark_dir && \
    mkdir -p build && \
    cd build && \
    cmake .. -DBENCHMARK_ENABLE_TESTING=OFF -DCMAKE_BUILD_TYPE=Release && \
    make && make install

cd $CWD