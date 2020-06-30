#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 
stdx_simd_url="https://github.com/VcDevel/std-simd/releases/download/simd-1.0.0/simd-1.0.0.tar.gz"
stdx_simd_file="simd-1.0.0.tar.gz"
stdx_simd_dir="simd-1.0.0"

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

wget -O $DEST/$stdx_simd_file $stdx_simd_url

cd $DEST
tar -zxvf $stdx_simd_file

cd $stdx_simd_dir
bash install.sh

cd $CWD