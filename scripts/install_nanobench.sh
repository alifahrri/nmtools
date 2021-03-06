#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 
url="https://raw.githubusercontent.com/martinus/nanobench/v4.3.0/src/include/nanobench.h"
file="nanobench.h"

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
    DEST="/opt/nanobench/"
    mkdir -p $DEST
fi

wget -O $DEST/$file $url

mkdir -p /usr/local/include/nanobench/
cp $DEST/nanobench.h /usr/local/include/nanobench/