#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 
nanobench_header_url="https://raw.githubusercontent.com/martinus/nanobench/v4.0.0/src/include/nanobench.h"

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
    DEST="/opt/nanobench/include/nanobench"
    mkdir -p $DEST
fi

wget -O $DEST/nanobench.h https://raw.githubusercontent.com/martinus/nanobench/v4.0.0/src/include/nanobench.h