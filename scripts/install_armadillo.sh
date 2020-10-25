#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
armadillo_url="https://sourceforge.net/projects/arma/files/armadillo-10.1.0.tar.xz"
armadillo_file="armadillo-10.1.0.tar.xz"
armadillo_dir="armadillo-10.1.0"

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

wget -O $DEST/$armadillo_file $armadillo_url

cd $DEST
tar -zxvf $armadillo_file

cd $armadillo_dir
mkdir -p build && cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local/ .. && make install

cd $CWD