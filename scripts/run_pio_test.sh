#!/bin/bash

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
    echo "please provide test case directory! e.g. -d arduino/ufuncs"
    exit 1
fi

pio package pack --output nmtools.tar.gz
cp nmtools.tar.gz tests/platformio/${DEST}
cd tests/platformio/${DEST}
bash ../download-toolchain.sh
pio test -v --without-uploading --without-testing