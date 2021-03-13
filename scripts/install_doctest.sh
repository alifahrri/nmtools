#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 
doctest_url="https://github.com/onqtam/doctest/archive/2.4.5.tar.gz"
doctest_file="2.4.5.tar.gz"
doctest_dir="doctest-2.4.5"

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
    DEST="$HOME/tmp"
    mkdir -p $DEST
fi

wget -O $DEST/$doctest_file $doctest_url

cd $DEST && tar -zxvf $doctest_file

cd $doctest_dir && mkdir -p build && cd build && cmake -DDOCTEST_WITH_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local/ .. && make install

cd $CWD